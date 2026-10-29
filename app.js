/* プレおむ — 画面をまたいで「どの猫か」を引き継ぐ共通スクリプト */
(function () {
  var KEY = "preomu-state";

  /* 猫のタイプ別の「部屋で起きそうなこと」。level は起きやすさの目安(1〜3) */
  var TYPES = {
    active: {
      label: "活発・高いところ好き",
      likes: "走ることと、高い場所",
      problems: [
        {
          icon: "🪟", title: "カーテンや棚の上に登る", level: 3,
          bad: "高い場所が大好き。カーテンやタンスの上に登って、飾りや物を落としてしまうことがあります。",
          good: "窓際にキャットタワーなど、安全に上り下りできる場所を用意。壊れやすい物は高い所に置かないようにしましょう。",
          product: { name: "突っ張り式キャットタワー", note: "部屋の高さに合わせて選べるタイプ" }
        },
        {
          icon: "🌙", title: "夜や明け方に走り回る", level: 2,
          bad: "元気がありあまっていると、夜や明け方に走り回ることがあります。",
          good: "寝る前に、じゃらしなどでしっかり遊ぶ時間をつくると、落ち着きやすくなります。",
          product: { name: "じゃらし・おもちゃセット", note: "毎日の遊びの時間に" }
        },
        {
          icon: "🧶", title: "ひもや小さな物を口に入れる", level: 2,
          bad: "動くものに夢中になり、ひもや輪ゴム、小さな物をくわえてしまうことがあります。",
          good: "ひもや小物は蓋つきの箱などにしまい、床や机の上に置きっぱなしにしないようにしましょう。",
          product: { name: "蓋つき収納ボックス", note: "小物の片づけに" }
        }
      ]
    },
    curious: {
      label: "好奇心旺盛",
      likes: "おもちゃ遊びと、窓の外を見ること",
      problems: [
        {
          icon: "🛋️", title: "ソファや壁で爪とぎをする", level: 3,
          bad: "お気に入りの場所で爪とぎをして、家具や壁が傷つくことがあります。",
          good: "爪とぎ器を、よく爪とぎをする場所の近くに置きます。素材や形を変えて、好みを探しましょう。",
          product: { name: "段ボール・麻ひもの爪とぎ", note: "素材を変えて試せます" }
        },
        {
          icon: "🚪", title: "玄関や窓から外に出ようとする", level: 2,
          bad: "好奇心から、玄関の扉や窓のすき間から外に出ようとすることがあります。",
          good: "完全室内飼いを前提に、玄関に脱走防止柵を付け、窓は網戸にロックを付けましょう。",
          product: { name: "玄関用の脱走防止柵", note: "賃貸でも設置しやすいタイプ" }
        },
        {
          icon: "☕", title: "机の上の物を触って落とす", level: 2,
          bad: "動く物や光る物に興味を持ち、前足で触って落とすことがあります。",
          good: "割れ物や大事な物は戸棚にしまい、机の上は片づけておきましょう。",
          product: { name: "落下防止の固定グッズ", note: "小物や家電の固定に" }
        }
      ]
    },
    calm: {
      label: "落ち着いた性格",
      likes: "静かな場所で、ゆっくり休むこと",
      problems: [
        {
          icon: "🛏️", title: "来客や大きな音で隠れる", level: 2,
          bad: "来客や大きな音が苦手で、しばらく出てこないことがあります。",
          good: "ひとりで安心して休める隠れ場所を用意し、無理に出さずに様子を見ましょう。",
          product: { name: "猫用ハウス・ベッド", note: "落ち着ける隠れ場所に" }
        },
        {
          icon: "🎯", title: "運動不足になりがち", level: 2,
          bad: "静かに過ごすのが好きなので、動く機会が少なくなりがちです。",
          good: "短い時間でも、毎日一緒に遊ぶ習慣をつくりましょう。",
          product: { name: "ゆっくり動くおもちゃ", note: "マイペースな猫向き" }
        },
        {
          icon: "🚽", title: "トイレが合わないと別の場所で用を足す", level: 1,
          bad: "トイレの場所や砂が気に入らないと、別の場所で用を足すことがあります。",
          good: "静かで落ち着ける場所に置き、掃除をこまめに。合わなければ砂の種類を試しましょう。",
          product: { name: "猫用トイレ(複数タイプ)", note: "広さや形を選べます" }
        }
      ]
    }
  };

  /* 猫ごとの3Dモデルがないときに使う、共通のモデル */
  var DEFAULT_MODEL = "./domestic-cat-sitting.glb";

  var SAMPLES = [
    { id: "mike", name: "ミケ", photo: "./mike.jpg", type: "curious", model: "./mike.glb" },
    { id: "sora", name: "ソラ", photo: "./sora.jpg", type: "active", model: "./sora.glb" },
    { id: "momo", name: "モモ", photo: "./momo.jpg", type: "calm", model: "./momo.glb" }
  ];

  function load() {
    try { return JSON.parse(sessionStorage.getItem(KEY)) || null; } catch (e) { return null; }
  }

  function save(state) {
    try { sessionStorage.setItem(KEY, JSON.stringify(state)); return true; } catch (e) { return false; }
  }

  /* 直接このページを開いたとき用に、状態がなければミケを仮に使う */
  function current() {
    var s = load();
    if (s && s.type && TYPES[s.type]) return s;
    var d = SAMPLES[0];
    return { name: d.name, photo: d.photo, type: d.type, model: d.model, generated: false };
  }

  function reset() {
    try { sessionStorage.removeItem(KEY); } catch (e) { /* 何もしない */ }
  }

  var STEP_NAMES = ["写真", "3Dモデル", "AR", "暮らし"];

  function renderSteps(n) {
    var el = document.getElementById("steps");
    if (!el) return;
    el.innerHTML = STEP_NAMES.map(function (t, i) {
      var cls = i + 1 === n ? "on" : i + 1 < n ? "done" : "";
      return '<li class="' + cls + '"><b>' + (i + 1) + "</b><span>" + t + "</span></li>";
    }).join("");
  }

  window.Preomu = {
    TYPES: TYPES, SAMPLES: SAMPLES, DEFAULT_MODEL: DEFAULT_MODEL,
    load: load, save: save, current: current, reset: reset, renderSteps: renderSteps
  };
})();
