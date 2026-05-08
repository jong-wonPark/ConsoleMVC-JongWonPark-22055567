# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 빌드 명령어

**Visual Studio 2022** (권장):
```powershell
# GUI에서 Build > Build Solution (F7)

# CLI에서 msbuild 사용
msbuild ConsoleMVC\ConsoleMVC.vcxproj /p:Configuration=Debug /p:Platform=x64
msbuild ConsoleMVC\ConsoleMVC.vcxproj /p:Configuration=Release /p:Platform=x64
```

**실행**:
```powershell
ConsoleMVC\x64\Debug\ConsoleMVC.exe
```

**컴파일러 요구사항**: Visual Studio 2022, C++20 (`stdcpp20`), UTF-8 인코딩 (`/utf-8` 옵션 적용됨)

테스트 프로젝트는 현재 없음 — 단위 테스트 프레임워크 미구성 상태.

## 아키텍처 개요

5계층 MVC 구조로, `AppController`가 모든 의존성을 소유하고 생성자 초기화 리스트에서 조립한다.

```
View → Controller → Service → Repository → Model
```

**의존성 흐름** (`AppController` 생성자에서 수동 DI):
```
Repositories (OrderRepo, InventoryRepo, ProductRepo, CustomerRepo, ProductionRepo)
    ↓ 참조(reference)로 주입
Services (OrderService, InventoryService, ProductionService)
    ↓ 참조로 주입
Controllers (OrderController, InventoryController, ProductionController)
```

모든 Repository는 `std::vector` 기반 인메모리 저장소이며 `seedData()`로 초기 데이터를 적재한다. DB 연동 없음.

## 계층별 역할

**Model** — 데이터 구조만. 순수 계산 메서드(`Order::totalAmount()`, `ProductionOrder::progressRate()`, `InventoryItem::availableQuantity()`)가 여기에 위치한다.

**Repository** — CRUD + 필터 쿼리(`findByStatus()`, `findLowStock()`). 비즈니스 규칙 없음.

**Service** — 핵심 비즈니스 로직. 여러 Repository를 조율하는 트랜잭션성 동작이 여기에 있다. 예: `OrderService::approveOrder()`는 재고 확인 후 예약까지 한 번에 처리.

**Controller** — 사용자 입력 수집 → Service 호출 → View로 결과 전달. 직접 Repository를 호출하지 않는다.

**View** — 콘솔 출력 및 입력 수집만. 비즈니스 로직 없음.

## 핵심 비즈니스 흐름

### 주문 상태 전이
```
Pending → Approved (재고 예약 발생)
        → Rejected
Approved → Shipping → Completed (실재고 차감 + 예약 해제)
```
`OrderService::approveOrder()`에서 `InventoryRepository::updateReserved()`를 직접 호출하여 재고를 예약한다. `completeShipment()`에서 실재고를 차감하고 예약을 해제한다.

### 생산 상태 전이
```
Planned → InProgress → Completed (자동 재고 입고)
                     → Paused → InProgress
```
`ProductionService::completeProduction()`이 완료 시 `InventoryService::receiveFromProduction()`을 호출하여 재고를 자동 증가시킨다.

### 재고 예약 모델
`InventoryItem`은 `quantity`(실재고)와 `reservedQuantity`를 별도 관리한다. `availableQuantity() = quantity - reservedQuantity`. 주문 승인 시 예약, 출고 완료 시 실재고 차감 및 예약 해제.

## 코드 규칙

- 멤버 변수명은 `trailing underscore` 사용 (`orderService_`, `orderRepo_`)
- Service 메서드는 성공/실패를 `bool` 또는 `std::optional`로 반환
- 한글 출력은 `SetConsoleCP(CP_UTF8)` + `SetConsoleOutputCP(CP_UTF8)` 설정 전제 (`main.cpp`에서 처리)
- 새 도메인 추가 시: Model → Repository → Service → Controller → View 순으로 구현하고, `AppController`에 의존성 연결
