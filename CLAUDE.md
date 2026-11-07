# プレおむ(ハッカソン作品)— 引き継ぎメモ

ローカルの Claude Code が、この文書を最初に読んで作業を続けるためのメモです。
**APIキーなどの秘密は、ここにもコードにも書かない**(Cloudflare の Secret にだけ置く)。

## これは何か
- 「プレおむ」= ねこをお家にプレお迎え。保護猫を迎える前に、猫との暮らしを想像してもらうWebサービス。
- 主役: 迎えたい気持ちを後押しする。補助: 起きそうな問題と対策を見せ、迎えた後のギャップを減らす。
- ハッカソン(TERACKATHON 10回)の最終発表は2026-11-08の昼過ぎ。7分、聞き手はサポーターと企業。
- 評価5項目(各10点): 実装点 / 技術点 / 領域理解 / 新規性・将来性 / インパクト(事業性)。
- ユーザーは工学部の大学生。プログラミングは初心者+α。猫部でTNR活動をしている。
  手順を指示するときは、「今何をしているか」の説明を添えて学べるようにする。

## 構成(GitHub Pages の静的サイト)
- 公開URL: https://takabo190106-pixel.github.io/cater/ (main ブランチに push すると公開される)
- 画面の流れ(全4ステップ): index.html → STEP 01 upload.html(猫を選ぶ) → STEP 02 model.html(3D)・ar.html(AR) → STEP 03 room.html(猫の目で部屋を見る) → STEP 04 compare.html(対策前後の比較、費用、締めくくり)
- 3Dモデルは写真から生成していない。事前に作ったサンプルを表示し、画面にもそう書いている
- 見た目: ムードボードの鉛筆スケッチ調のモノクロ。style.css に集約。猫とアイテムのイラスト(*.svg)はオリジナルで、ムードボードの絵は使っていない
- app.js: 状態管理(sessionStorage の `preomu-state` と `preomu-room`)、SAMPLES(ソラ・ミケ・モモ。各自の .glb)、DEFAULT_MODEL
- 3D: `<model-viewer>` 4.0.0、GLBは軽量版(ミケ0.9MB、モモ約1MB、ソラ約4MB)
- problems.html と app.js の TYPES(性格別の問題)は、新しい流れでは使っていない
- worker/index.js: 部屋の写真をGeminiに送る中継(Cloudflare Worker)。config.js の `window.PREOMU_API` にそのURLを入れる

## 部屋写真AI(room.html)の仕組み
ブラウザ → Cloudflare Worker(キーを持つ) → Google Gemini → JSON → 画面
- Worker URL: https://broad-union-83be.takabo190106.workers.dev (Cloudflare アカウント takabo190106@gmail.com)
- Worker の変数: `GEMINI_API_KEY`(Secret)、`GEMINI_MODEL`(Text)
  - `GEMINI_MODEL` は `gemini-3.5-flash-lite`(無料枠: 15回/分、500回/日。2026-11-07 にAI Studioで確認)。
- config.js の `PREOMU_API` には、上のURLが入っている。
- AIにつながらないときは、「事前に用意した例」を、その旨を明示して表示する(偽の判断を見せない)。
- 無料枠のみ使う。Googleの課金は有効にしない。
- Gemini の画像生成モデルは無料枠が0回(2026-11-07 にAI Studioで確認)。compare.html の「対策しない場合」の画像は Cloudflare Workers AI(無料枠。超えるとエラーになるだけで課金されない)で作り、写真は Cloudflare にも送られる。「対策した場合」は、ユーザーがイラストを自由に重ねる。
- worker/index.js を変えたら、Cloudflare のエディタにも同じ変更を入れて Deploy する(push だけでは反映されない)。

## 今後の作業(ユーザーの計画)
1. スライドを一から作り直す(現行: https://claude.ai/artifact/1zmAKG9aEfRuFPu5ASHbi4 は古い)。発表は2026-11-08の昼過ぎ
2. 余力があれば、ARでキャットタワーやトイレを置けるようにする

## 現在の機能(スライドの材料)
- 部屋写真: AIが家具など部屋にずっとあるものを見つけ、写真に枠を表示。猫の顔アイコン(良い点・悪い点で表情が違う)の吹き出しでコメントし、悪い点には対策を添える
- 対策しない場合: 挙がった問題だけをもとに、いたずら後のイメージ画像をAIが生成(Workers AI の FLUX.2 Klein)
- 対策した場合: 8種類のイラスト(タワー、ベッド、トイレ、爪とぎ、コードカバー、食器と水、寝ている猫、歩いている猫)をユーザーが自由に配置・拡大縮小
- 費用: 初期費用 約7万円、月 約8,000円を目安として表示(ユーザーの指定。出典は未確認)
- 未確認: 生成画像の質は実際の部屋写真で検証中。無料枠で1日に何枚作れるかは未測定

## 守ること(誠実さ)
- 実際に行っていないヒアリングや数字を、発表資料に書かない。
  ヒアリングは友人2人+保護猫団体1件のみ。メーカーへのヒアリングと、収益の数字は、まだ未確認(仮定と明記)。
- AIの結果は推測だと、画面に書く。写真がGoogle Geminiに送られることも、画面で知らせる。
- 3Dモデルのメッシュは、自前で間引かない(ひび割れが出た)。軽くしたいときはMeshy側でRemeshする。

## コミットの慣習
- push前に `git pull --ff-only`。
