# scheduler

**実行コマンド**

gcc -std=c99 scheduler.c 

-windows環境下

a.exe


-linux環境下

./a.out

**内容**

スケジューリング (以下を実装)

・処理時間順

・到着準

・ラウンドロビン

**その他**

ラウンドロビンの定時間を変更するなら → scheduler.c L3 のFIXED_TIMEに設定。

プロセスを変更する → scheduler.txtを変更し プロセス数をscheduler.c L2のProcessNumberに設定。