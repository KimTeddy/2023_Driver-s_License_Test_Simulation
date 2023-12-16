#!/bin/bash

# 드라이버 파일들의 배열 정의
drivers=("buttondrv.ko" "buzzerdrv.ko" "fnddrv.ko" "leddrv.ko" "textlcddrv.ko")

# 배열에 있는 각 드라이버를 순차적으로 로드
for driver in "${drivers[@]}"
do
    echo "loading: $driver"
    sudo insmod "$driver"
    if [ $? -eq 0 ]; then
        echo "SUCCESS: $driver ins complete"
    else
        echo "ERROR: $driver ins Failed"
        exit 1  # 실패 시 스크립트 종료
    fi
done

echo "insmod all complete"