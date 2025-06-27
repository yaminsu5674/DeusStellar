# 🌌 DeusStellar – 행성 수호 비행 FPS 게임

## 🎮 게임 장르

3D 우주 비행 슈팅 FPS

## 📖 게임 소개

<img src="https://cdn.pixabay.com/photo/2021/09/18/09/45/space-6636044_1280.jpg" width="600" />

**DeusStellar**는 우주 공간에서 적의 침략으로부터 자신의 행성을 방어하고, 반격을 통해 상대의 행성을 파괴하는 것을 목표로 하는 **3D 비행 슈팅 FPS 게임**입니다.

플레이어는 우주 공간에서 **자유롭게 비행하며**, 마우스와 키보드를 이용해 시점과 이동 방향을 조절하고, 적과의 전투를 통해 전략적 액션을 즐길 수 있습니다.

**다운로드 링크** https://drive.google.com/file/d/1xAULbjmYURCaLjlkp4rYylbxyQ4quuoG/view?usp=drive_link


- **기본 조작**
    - WASD: 방향 이동
    - 마우스 이동: 시점 전환
    - Shift: 대시
    - 좌클릭: 사격

---

## 🧰 기술 스택

- **게임 엔진:** Unreal Engine 5.5  
- **개발 IDE:** Visual Studio 2022  
- **언어:** C++, Blueprints  

---

## 🧩 주요 기능

### 1. 자유 비행 기반 조작 시스템

`CharacterMovementComponent`를 **Fly 모드**로 설정하고, 마우스 기반 시점 전환 및 `WASD + Shift` 입력 조합으로  
**대시 및 방향 전환이 자유로운 3D 우주 비행**을 구현했습니다.

- `WASD`: 이동  
- `Shift`: 대시  
- `마우스`: 시점 전환  
- `좌클릭`: 기본 공격  

---

### 2. 비행 애니메이션 시스템

**BlendSpace + AnimStateMachine**을 활용하여,  
플레이어의 속도 및 이동 방향에 따라 **자연스럽게 전환되는 비행 애니메이션**을 구성하였습니다.

- 방향 변화, 속도 변화에 따른 애니메이션 블렌딩  
- 스무스한 시각적 전환  

---

### 3. 적 AI 시스템 (Behavior Tree 기반)

적 AI는 Unreal의 **Behavior Tree**를 기반으로 구현되었으며, 다음과 같은 동작을 수행합니다:

- 기본적으로 **플레이어의 행성에 접근**  
- 일정 거리 이내로 플레이어가 접근하면 **타겟을 전환하여 공격**  
- `BTTask`, `Blackboard`, `Service` 등을 통해 공격 조건 분기 및 이동 상태 판단  

---

