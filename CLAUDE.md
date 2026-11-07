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
- 画面の流れ: index.html → upload.html(猫を選ぶ) → model.html(3D) → ar.html(AR) → room.html(猫の目で部屋を見る)
- app.js: 状態管理(sessionStorage の `preomu-state`)、SAMPLES(ソラ・ミケ・モモ。各自の .glb)、DEFAULT_MODEL
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

## 今後の作業(ユーザーの計画)
1. スマホで部屋写真を試す(Worker の修正と config.js の push は済み)
2. ムードボード(ユーザーが後で渡す)に合わせて、サイト全体を再設計
3. 猫の対策を「性格と問題の紐づけ」から「部屋写真を猫の目線で解説」へ(1の機能が土台)
4. スライドを一から作り直す(現行: https://claude.ai/artifact/1zmAKG9aEfRuFPu5ASHbi4 は古い)
5. 余力があれば、ARでキャットタワーやトイレを置けるようにする

## 守ること(誠実さ)
- 実際に行っていないヒアリングや数字を、発表資料に書かない。
  ヒアリングは友人2人+保護猫団体1件のみ。メーカーへのヒアリングと、収益の数字は、まだ未確認(仮定と明記)。
- AIの結果は推測だと、画面に書く。写真がGoogle Geminiに送られることも、画面で知らせる。
- 3Dモデルのメッシュは、自前で間引かない(ひび割れが出た)。軽くしたいときはMeshy側でRemeshする。

## コミットの慣習
- push前に `git pull --ff-only`。
