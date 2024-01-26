# Embedded System
<table>
  <tr>
    <td>강의명</td>
    <td>2023-2학기 임베디드시스템, 2023.09~12</td>
  </tr>
  <tr>
    <td>프로젝트 명</td>
    <td>운전면허 장내기능시험 모의 시뮬레이션</td>
  </tr>
</table>
<pre>
    
</pre>

- 전체 모습<br>
![KakaoTalk_20231221_053445868](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/484a86e7-2857-44dd-b669-3461553506f5)

- TFT-LCD & PERI Board<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/fed32960-c538-47cf-b5b7-b6427de96460" width="30%">
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/b2aab785-53db-4fb3-a63e-aa09f30d3eb5" width="35%">
<!--![리사이즈KakaoTalk_20231221_004957180](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/fed32960-c538-47cf-b5b7-b6427de96460)-->
<!--![KakaoTalk_20231221_004850454](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/b2aab785-53db-4fb3-a63e-aa09f30d3eb5)-->

# 프로젝트 목차
0. [초기 개발 모습](#0-초기-개발-모습)<br>
1. [제안 아이디어](#1-제안-아이디어)<br>
    a. [제안 배경]()<br>
    b. [아이디어 기술]()<br>
2. [연구방법]()<br>
    a. [SW 구성도]()<br>
    b. [Flow Chart]()<br>
3. [설계]()<br>
    a. [실행과정]()<br>
    b. [작동]()<br>
4. [결과]()<br>
    a. [결론]()<br>
    b. [시연]()<br>
5. 부록
<br>- Commit Graph

## 0. 초기 개발 모습
- OpenGL 사용, 3D 그래픽 구현
- 프로젝트 제한조건->Xwindow 사용 불가로 인해 폐기
![KakaoTalk_20231221_022149236](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/f3162c6e-9d3a-416f-9905-bf8205e7b953)

## 1. 제안 아이디어
### a. 제안 배경
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/eb7cd5c1-2cbd-42bf-9dfb-511cc9f423d8)
출처 : 통계청
- 점점 떨어지고 있는 운전 면허 시험 합격률
- 초보 운전자의 운전 미숙으로 인한 다양한 사고 발생 등의 사회적인 문제<br>
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
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/5a7b5e60-a5e1-49de-bbba-7144e60649db" width="60%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/5a7b5e60-a5e1-49de-bbba-7144e60649db)-->
### b. Flow Chart
- main<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/e5a5acbc-1255-4ac9-84d8-3f9fcfc88e0d" width="80%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/e5a5acbc-1255-4ac9-84d8-3f9fcfc88e0d)-->
- Button & LED Thread<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/0ca8c03b-cf96-4343-b041-1145b22e1fd5" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/0ca8c03b-cf96-4343-b041-1145b22e1fd5)-->
- Buzzer & FND Thread<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/45f769ee-42f9-4b44-8542-2517aacbc28e" width="40%">
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/9457c723-9f0b-4f47-9cd1-4894134732ee" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/45f769ee-42f9-4b44-8542-2517aacbc28e)-->
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/9457c723-9f0b-4f47-9cd1-4894134732ee)-->
- Traffic Light Thread<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/4701e529-dc3f-443d-8b3f-81d15c5a0897" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/4701e529-dc3f-443d-8b3f-81d15c5a0897)-->
- Accelerometer Thread<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c5326f79-51d9-4c33-9a03-ea0291902abc" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c5326f79-51d9-4c33-9a03-ea0291902abc)-->


## 3. 설계
### a. 실행과정
- Makefile
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/a7d0351b-880a-400c-99fc-51c55a3d215d)
### b. 작동
- Button & LED
    - 안전벨트 / 사이드 브레이크 / 좌측 방향지시등 / 비상등 / 우측 방향지시등 / 기어
    - 키트의 6개의 버튼으로 자동차 제어에 사용되는 기능 요소 구현.
    - 각 버튼을 누르면 LED가 On/Off 되며 현재 상태 표시.<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c238fb3c-0429-45bb-b0aa-87307b4b4a45" width="40%"><!--![SmartSelect_20231221_045426_Gallery-ezgif com-resize (1)](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c238fb3c-0429-45bb-b0aa-87307b4b4a45)-->
    - 방향지시등 / 비상등의 경우 실제와 같이 깜빡임.<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/d675a11e-160a-43b1-a85e-2d3721de3157" width="40%">
<!--![SmartSelect_20231221_043547_Gallery-ezgif com-resize](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/d675a11e-160a-43b1-a85e-2d3721de3157)-->
- FND(KimTeddy 담당)
    - [“현재점수” “감점될 점수”] 형식으로 표시.
    - 7-Segments 6자리 중 3-digit 사용, 현재 점수가 정확하게 표시됨.
    - 오른쪽 2-digit은 감점 발생 시 감점될 점수 출력.
    - 감점 점수는 4번 깜빡이고, 현재 점수에서 0.07초 간격으로 1씩 감소하는 애니메이션이 끝나면 마지막으로는 감점 점수를 뺀 현재 점수만 남게 띄움.<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/55f56318-1a87-4ecb-b421-f4bc3e5fe0c1" width="40%">
<!--![KakaoTalk_20231221_030458642-ezgif com-resize](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/55f56318-1a87-4ecb-b421-f4bc3e5fe0c1)-->

- Color LED
    - 빛의 3원색 RGB를 이용하여 신호등 빨강, 주황, 초록불 구현.
    - 신호등 불빛으로 교차로에서 빨간 불일 때  차량이 교차로를 지나면 실격처리!<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/401bddce-b0d8-4e9d-9b4e-1ff345532bfd" width="30%"><br>
<!--![KakaoTalk_20231221_043853273](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/401bddce-b0d8-4e9d-9b4e-1ff345532bfd)<br>-->
<div align=center>
<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/5a65d307-c6f9-4ef5-82f6-a2ff4a761b83" width="20%">
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/e7959895-1e8b-4d28-a253-44b56ab01573" width="20%">
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/7fe07c0a-176e-45c8-9bf3-665bd88b67e1" width="20%">
</div>
<!--![KakaoTalk_20231221_0204207672](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/5a65d307-c6f9-4ef5-82f6-a2ff4a761b83)-->
<!--![KakaoTalk_20231221_020420767_012](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/e7959895-1e8b-4d28-a253-44b56ab01573)-->
<!--![KakaoTalk_20231221_020420767_022](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/7fe07c0a-176e-45c8-9bf3-665bd88b67e1)-->

- Buzzer
    - 주행 시작 시 ”START 알림음”
    - 비상등과 방향등을 켰을 시 ”깜빡이 소리”
    - 각 단계들 넘어갈 시 “마리오 1UP 효과음”
    - 돌발상황 발생할 시 “돌발 경고음”
    - 감점 시 “감점 알림음”<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/e64dd029-2630-4581-a42b-d531d1963dd1" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/e64dd029-2630-4581-a42b-d531d1963dd1)-->
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/4a49148f-f573-40c6-8300-93b713def9d0)-->
- Accelerometer
    - 시뮬레이션이 START되면 시작 당시의 Accel센서 값을 저장한 후, while문을 돌며 현재 Accelerometer 값과 초기 Accelerometer 값을 비교.
    - 비교된 값으로 핸들(키트)이 얼마나 기울었는지 판단하여 좌회전, 우회전, 서행, 가속, 브레이크를 구별할 수 있도록 구현.<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/2ef9e886-4236-4528-b237-e307ff674eea" width="20%">
<!--![KakaoTalk_20231221_014546901](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/2ef9e886-4236-4528-b237-e307ff674eea)-->

- TFT LCD(bmp+frame buffer)
    - TFT_LCD에 각 상황에 따라다른 화면을 출력하여 시뮬레이션 진행.
    - 시뮬레이션에서는 키트의 기울기에 따라 bmp이미지가 교체되며 애니메이션처럼 동작.
    - Manual 기능
        - 이전/이후 화면으로 넘기는 버튼이 화면 하단에 오버레이로 출력됨.
        - 끝 페이지에서는 더 이상 넘어가지 않고 시뮬레이션 시작 버튼이 보임.<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c65bba4a-af38-42fb-9802-1d625703c9c3" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/c65bba4a-af38-42fb-9802-1d625703c9c3)-->
- TFT LCD(bmp overlay)
    - TFT LCD에 각 상황에 따라안내 메시지와 UI를 오버레이하여 띄움.<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/cce5b93e-e409-4bcf-89c7-c4d8b8f7ce8c" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/cce5b93e-e409-4bcf-89c7-c4d8b8f7ce8c)-->
- LCD Touch Screen (bmp overlay)
    - 기본 조작 평가에 나오는 전조등, 와이퍼, 시동 켜기 버튼을 TFT-LCD에 이미지로 구현하여 해당 영역을 터치했을 때 On/Off동작을 하도록 구현.
    - Manual 등 다양한 화면 전환에 터치 스크린을 활용.<br>
&nbsp;<img src="https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/f39ba0ea-6e4a-4920-a427-c17ef7a04511" width="40%">
<!--![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/f39ba0ea-6e4a-4920-a427-c17ef7a04511)-->

## 4. 결과
### a. 결론
- 본 프로젝트를 통해 운전면허 장내 기능 시험의 시뮬레이션을 구현하는 과정에서 다양한 하드웨어 및 소프트웨어 요소들이 어떻게 상호작용하는지 이해할 수 있었다. 
- LED, 버튼, Buzzer, Text LCD, 가속도 센서 등 다양한 센서의 디바이스 드라이버들을 활용하여 프로젝트를 수행하고자 노력했다.
  이 과정에서 기기들 간의 상호 연결 및 통신에 대한 이해를 향상시키고, 리눅스 시스템에 대한 지식을 확장할 수 있었다. 
- 이를 바탕으로, 팀원들간의 원활한 협업을 함으로써, 이번 임베디드시스템 프로젝트를 잘 마무리할 수 있었다.

### 5. 부록
- Commit Graph
![image](https://github.com/KimTeddy/EmbeddedSystem/assets/68770209/d9d83fef-b4c1-44b8-b6ab-b5c5049b2d6f)
