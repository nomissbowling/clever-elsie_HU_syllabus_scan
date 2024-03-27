# HU_syllabus_scan
## 使い方
  1. WSLインストール
  1. このリポジトリをクローンする
  1. src/main.pyのurl_home=url+"urlの後半";で自分の学部のシラバスの"/"以後"2023_15.html"の部分をコピペする。(_15は情報科学部、総科は01、文学は02だったのでシラバスホームの上からの並び順だと思われる)
  1. UTF-8が正しく表示される環境のターミナルでMakefileと同じディレクトリに移動する
  1. 初回は`make build`、2回目以降は`./main`か`make run`。`make`が失敗する場合は、下の環境構築の部分が失敗してるので手動でガンガレ。
  1. エクセル->上のリボンの「データ」の左から2番目の「テキストまたはCSVから」データの取得と変換を押し、syl.csvを選択
  1. またはインタラクティブな操作を行う
  + 注意点として、2回目以降の起動でもダウンロードしたデータから.csvを組みなおすため起動に3秒ほどかかります。初回のダウンロード時はネットワーク環境次第ですが最低30秒ほどダウンロードに時間がかかると思います。
## インタラクティブモード
  + 学年 タームの順番で空白か改行区切りで入力するとその年度の授業の情報の概要を出力する
  + 具体的には「授業名」、「教師名」、「開講期間」、「曜日・時限・教室」、「成績評価」
  + それぞれの授業が1行で表示され、表示された順番に0から始まるIDが割り振られている
  + IDを入力するとその授業の詳細が表示される。
  + IDの範囲外の数字を入力するとまた学年、タームの選択に戻り無限ループ
  + 学年もタームも0を入力すると終了する
## calc05unit.xlsx
  05情科の学生便覧を人力写経して単位を計算するエクセルシート。  
  履修計画の立案なり、留年カウントダウンなり、好きに使ってください。  
  05以外の便覧とは恐らく授業の構成や時期が異なると思うので、それ以外の人は自分の便覧を見てね！！  
  (例えば人工知能概論とかベイズ統計とかは04の便覧には載って無かったようなうろ覚えの記憶がある。)

## 環境構築(WSL-Ubuntu)
  1. `sudo apt update`でUbuntuを最新にする。失敗する場合は下の方の対処法をどうぞ。`sudo`初回はパスワード設定が必要。
  1. GCC,makeのインストール`sudo apt install build-essential`
  1. pythonのインストール`sudo apt install python3 -y`
  1. pip,venvのインストール`sudo apt install python3-pip python3-venv`
  1. requests,beautifulsoup4のインストール
    1. `python3 -m pip install requests`
    1. `python3 -m pip install beautifulsoup4`

## sudo apt update 失敗するとき
  1. `sudo rm /etc/resolv.conf`
  1. `sudo sh -c "echo 'nameserver 8.8.8.8' > /etc/resolv.conf"`
  1. `sudo sh -c "echo '[network]\ngenerateResolvConf = false' > /etc/wsl.conf"`

## 利用に関する注意
  コードの改変はご自由にどうぞ。
  改変の有無に関わらず、コードやバイナリの再頒布は禁止とします。
  githubリポジトリのURLによってのみこのプログラムを共有することを許可します。
  URLの共有先はいかなるメディアでも構いませんが、大学事務や教員に共有するのは恥ずかしいのでやめてね♡
