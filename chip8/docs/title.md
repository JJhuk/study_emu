# CHIP - 8 에뮬레이터 / 처음 만나는 에뮬레이터

# 들어가기 전에,

이 문서는 에뮬레이터를 처음 만드는 프로그래머를 위해 만들어졌습니다. 이 문서를 읽는 데 아래와 같은 기술이 필요합니다. 

- 비트 연산에 대한 이해. ( 적어도, OR, AND, bit shift가 뭐하는 것인지는 알 정도. )
- C++ 기초, 포인터, 배열, 클래스에 대한 이해.

추가적으로, 있으시다면 더 이해가 잘 될 만한 기술입니다. 다만 아래 기술은 본 예뮬레이터 제작을 하면서 배우게 될 주된 기술들이므로 모르셔도 이 문서를 이해하시는 데엔 지장이 없습니다.

- 레지스터, Program Counter 등 CPU에 구조에 대한 간략한 이해.
- OpenGL 프로그래밍

이 문서를 쓰면서 생각한 주요 독자는 :

- 게임을 좋아하고, 콘솔을 좋아하여 만들어보고 싶은 분.
- 에뮬레이터를 만들어 보고 싶은데, 어디부터 시작해야 할지 모르시겠다는 분.
- 로우 레벨에 대한 지식을 익혀보고 싶으신 분.

그리고 마지막으로 당부해드리고 싶은 게 있습니다. 이걸 만들어보겠다는 의지를 가지셨다면. 숙제보다는 Just For Fun. 그냥 재미로 만들어보세요! 게이머로써 두근거리는 마음으로 에뮬레이터를 만드시면서. 이 문서가 도움이 되었다면 그것보다 기쁜 일은 없을거에요!

그러면. 부디 즐겁게 읽어주세요 'ㅁ'! 

# 개요

에뮬레이터라는 프로그램은 딱히 우리들에게 낯선 존재가 아니었어요. 옛날에 학교 컴퓨터 실에서 선생님 몰래 했던 '포켓몬스터 금/은'은 게임 보이 에뮬레이터로 구동시켰고. 컴퓨터로 메탈슬러그를 해보셨다면. 이미 에뮬레이터를 만져 보시고, 해보신 적도 있는거에요! 

그럼에도 생각보다 많이 봐왔음에도 불구하고 프로그래밍으로써 '에뮬레이터'는 낯설고, 두렵고, 무언가 신비로운 위치에 있었습니다. 저는 그렇게 느꼈었어요. 에뮬레이터는 옆에는 해부한 콘솔을 들고 있는 무시무시한 Geek이 구석에서 놀라운 타이핑으로 만들어야만 만들 수 있는. 초고난이도 기술 중에 하나라고 생각하여 손도 못 댔었습니다. 

그렇게 생각했던 제가 CHIP-8 이라는 기기를 만나고, 그걸 회사 퇴근하고 조금씩 만들어 2주 만에 완성하게 되었습니다. 만약 [https://github.com/danistefanovic/build-your-own-x](https://github.com/danistefanovic/build-your-own-x) '너의-무언가를-만들어보자' 레포지토리가 없었으면 여전히 저에게 에뮬레이팅은 무시무시한 영역이었을 것이고. [https://news.hada.io/](https://news.hada.io/) 항상 좋은 정보가 올라오는 GeekNews가 없었으면 저런 레포지토리가 있었는지도 몰랐을 거에요. 

이 강좌는 [http://www.codeslinger.co.uk/pages/projects/chip8.html](http://www.codeslinger.co.uk/pages/projects/chip8.html) 이 강좌를 따라하고, [http://devernay.free.fr/hacks/chip8/C8TECH10.HTM](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) 이 명세서를 보고 구현된 코드를 기반으로 설명할 거에요. 

# 에뮬레이터란?

에뮬레이터는 '다른 프로그램이나 장치를 모방한 프로그램, 혹은 전자기기의 능력'을 뜻해요.

# CHIP-8은?

# CPU Step 만들어보기

# 명령어를 검증하는 방법

우리는 실제로 ROM을 돌리면서 이 명령어들이 정상 작동하는지 테스트를... 할 거긴 한데. 지금 당장은 하지 않을거에요. 왜냐하면 :

- 명령어는 굉장히 빠른 속도로 진행되기 때문에, 기대값이 명확하지 않은 실제 구동 상황에서 모든 명령어의 세부사항을 점검할 수 없어요.
- 시각적으로 보이지 않는 것들 - 비트 연산과 사칙연산에 대한 결과. 레지스터가 잘 움직였는지에 대한 결과를 확인하기 어려워요.
- 자동으로 지금까지 구현했던 코드들이 모두 정상인지 확인하는 게 어려워요.

# 테스트를 위하여 준비해야 할 것들