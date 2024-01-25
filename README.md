# Embedded System2023.09~12
2023-2 임베디드시스템
## 초기 개발 - OpenGL 사용, 3D 그래픽 구현
- 프로젝트 제한조건->Xwindow 사용 불가로 인해 폐기
![KakaoTalk_20231221_022149236](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/f3162c6e-9d3a-416f-9905-bf8205e7b953)


1. 제안 아이디어<br>
    a. 제안배경<br>
    b. 아이디어기술<br>
2. 연구방법<br>
    a. FLOW CHART<br>
    b. 연구방법<br>
3. 설계<br>
    a. 실행과정<br>
    b. 작동<br>
4. 결과<br>
    a. 결론<br>
    b. 시연<br>

## 1. 제안아이디어
### a. 제안 배경
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/eb7cd5c1-2cbd-42bf-9dfb-511cc9f423d8)
출처 : 통계청
- 점점 떨어지고 있는 운전 면허 시험 합격률
- 초보 운전자의 운전 미숙으로 인한 다양한 사고 발생 등의 사회적인 문제
 ⇒ 현실적인 운전 경험을 모의로 제공하여 공간의 제약 없이 "운전면허 기능시험 모의 시뮬레이션"을 할 수 있도록 제작
1. 운전 면허를 취득할 사람이라면 누구나 통과해야할 장내 기능 시험을 시뮬레이션으로 구현
2. 시간과 공간의 제약 없이 시험해볼 수 있는 모의 시뮬레이션
3. 키트의 가속도 센서를 이용하여 키트를 핸들로 사용하는 시뮬레이션 제작
### b. 아이디어 기술
- Color LED와 FND, Text LCD, TFT LCD(+Overlay), Buzzer를 활용한 시각적&청각적 피드백
- TFT LCD를 통해 현재 운전자의 시야와 코스 내 구간을 한 눈에 확인하여 변화하는 환경에 즉각적으로 반응하면서 운전 능력을 높이고 주행 경험을 제공할 수 있는, "운전면허 기능시험 모의 시뮬레이션"
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/d1253b36-86ef-41ad-a9e3-b504e5e2abc4)

## 2. 연구 방법
### a. SW 구성도
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/5a7b5e60-a5e1-49de-bbba-7144e60649db)
### b. Flow Chart
- main
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/429e666b-5a70-4068-bfca-566aeb9b446a)
- Button & LED Thread
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/0ca8c03b-cf96-4343-b041-1145b22e1fd5)
- Buzzer & FND Thread
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/45f769ee-42f9-4b44-8542-2517aacbc28e)
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/9457c723-9f0b-4f47-9cd1-4894134732ee)
- Traffic Light Thread
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/4701e529-dc3f-443d-8b3f-81d15c5a0897)
- Accelerometer Thread
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c5326f79-51d9-4c33-9a03-ea0291902abc)


## 3. 설계
### a. 실행과정
- Makefile
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/a7d0351b-880a-400c-99fc-51c55a3d215d)
### b. 작동
- Button & LED
    - 안전벨트 / 사이드 브레이크 / 좌측 방향지시등 / 비상등 / 우측 방향지시등 / 기어
    - 키트의 6개의 버튼으로 자동차 제어에 사용되는 기능 요소 구현.
    - 각 버튼을 누르면 LED가 On/Off 되며 현재 상태 표시.
    - 방향지시등 / 비상등의 경우 실제와 같이 깜빡임.
![SmartSelect_20231221_045426_Gallery-ezgif com-resize (1)](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c238fb3c-0429-45bb-b0aa-87307b4b4a45)

- FND(KimTeddy 담당)
    - [“현재점수” “감점될 점수”]
    - 7-Segments 6자리 중 3-digit 사용, 현재 점수가 정확하게 표시됨.
    - 오른쪽 2-digit은 감점 발생 시 감점될 점수 출력.
    - 감점 점수는 4번 깜빡이고, 현재 점수에서 0.07초 간격으로 1씩 감소하는 애니메이션이 끝나면 마지막으로는 감점 점수를 뺀 현재 점수만 남게 띄움.
- Color LED
    - 빛의 3원색 RGB를 이용하여 신호등 빨강, 주황, 초록불 구현.
    - 신호등 불빛으로 교차로에서 빨간 불일 때  차량이 교차로를 지나면 실격처리!
![KakaoTalk_20231221_043853273](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/401bddce-b0d8-4e9d-9b4e-1ff345532bfd)
![KakaoTalk_20231221_0204207672](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/5a65d307-c6f9-4ef5-82f6-a2ff4a761b83)
![KakaoTalk_20231221_020420767_012](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/e7959895-1e8b-4d28-a253-44b56ab01573)
![KakaoTalk_20231221_020420767_022](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/7fe07c0a-176e-45c8-9bf3-665bd88b67e1)
- Buzzer
    - 주행 시작 시 ”START 알림음”
    - 비상등과 방향등을 켰을 시 ”깜빡이 소리”
    - 각 단계들 넘어갈 시 “마리오 1UP 효과음”
    - 돌발상황 발생할 시 “돌발 경고음”
    - 감점 시 “감점 알림음”
- Accelerometer
    - 시뮬레이션이 START되면 시작 당시의 Accel센서 값을 저장한 후, while문을 돌며 현재 Accelerometer 값과 초기 Accelerometer 값을 비교.
    - 비교된 값으로 핸들(키트)이 얼마나 기울었는지 판단하여 좌회전, 우회전, 서행, 가속, 브레이크를 구별할 수 있도록 구현.
- TFT LCD(bmp+frame buffer)


![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/4a49148f-f573-40c6-8300-93b713def9d0)

