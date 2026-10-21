
<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta name="theme-color" content="#faf6ef">
  <title>猫たちに会う — プレおむ</title>

  <script type="module"
    src="https://ajax.googleapis.com/ajax/libs/model-viewer/4.0.0/model-viewer.min.js">
  </script>

  <style>
    :root {
      --bg: #faf6ef;
      --paper: #fffdf9;
      --brown: #85543d;
      --dark: #5b392b;
      --text: #40352e;
      --muted: #81756c;
      --accent: #c17c57;
      --soft: #f0e5d8;
      --line: #eadfd3;
      --shadow: 0 8px 28px #59402b0d;
    }

    * { box-sizing: border-box; }
    html { scroll-behavior: smooth; }

    body {
      margin: 0;
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI",
        "Noto Sans JP", sans-serif;
      color: var(--text);
      background: var(--bg);
      line-height: 1.7;
    }

    button { font: inherit; cursor: pointer; }
    a { color: inherit; text-decoration: none; }

    .site-header {
      padding: 18px 24px;
      border-bottom: 1px solid var(--line);
      background: var(--bg);
    }

    .nav {
      max-width: 1080px;
      margin: auto;
      display: flex;
      justify-content: space-between;
      align-items: center;
      gap: 16px;
    }

    .logo {
      font-size: 25px;
      font-weight: 800;
      letter-spacing: -1px;
      color: var(--dark);
    }

    .logo span { color: var(--accent); }

    .nav-note {
      color: var(--muted);
      font-size: 13px;
    }

    main {
      max-width: 1080px;
      margin: auto;
      padding: 30px 24px 60px;
    }

    .page-heading { margin-bottom: 28px; }

    .eyebrow {
      margin: 0 0 8px;
      color: var(--brown);
      font-size: 12px;
      font-weight: 800;
      letter-spacing: 2px;
    }

    .page-heading h1 {
      margin: 0;
      color: var(--dark);
      font-size: clamp(28px, 4vw, 38px);
      line-height: 1.4;
    }

    .page-heading p:last-child {
      margin: 10px 0 0;
      color: var(--muted);
      font-size: 14px;
    }

    #cat-list {
      display: grid;
      grid-template-columns: repeat(3, minmax(0, 1fr));
      gap: 22px;
    }

    .cat-card {
      min-width: 0;
      padding: 12px;
      border: 1px solid #eee5db;
      border-radius: 20px;
      background: var(--paper);
      box-shadow: var(--shadow);
      transition: transform .2s, box-shadow .2s;
    }

    .cat-card:hover {
      transform: translateY(-3px);
      box-shadow: 0 14px 32px #59402b14;
    }

    .cat-photo {
      display: block;
      width: 100%;
      height: 250px;
      object-fit: cover;
      border-radius: 14px;
      background: var(--soft);
    }

    .cat-card-content { padding: 10px 5px 5px; }

    .cat-card h2 {
      margin: 4px 0 6px;
      color: var(--dark);
      font-size: 23px;
    }

    .cat-card p {
      min-height: 48px;
      margin: 0 0 16px;
      color: var(--muted);
      font-size: 13px;
    }

    .primary-button, .secondary-button {
      display: inline-flex;
      align-items: center;
      justify-content: center;
      padding: 12px 18px;
      border: 0;
      border-radius: 12px;
      font-weight: 700;
      transition: background .2s, transform .2s;
    }

    .primary-button {
      color: white;
      background: var(--brown);
    }

    .primary-button:hover {
      background: var(--dark);
      transform: translateY(-1px);
    }

    .cat-card .primary-button { width: 100%; }

    .secondary-button {
      color: var(--dark);
      background: var(--soft);
    }

    .secondary-button:hover { background: #e8d8c7; }

    #profile {
      display: none;
      max-width: 850px;
      margin: 0 auto;
    }

    .back-button { margin-bottom: 22px; }

    .profile-top {
      display: grid;
      grid-template-columns: minmax(0, 1fr) minmax(0, 1fr);
      gap: 28px;
      align-items: start;
    }

    #profile-photo {
      width: 100%;
      height: 380px;
      object-fit: cover;
      border-radius: 22px;
      background: var(--soft);
      box-shadow: var(--shadow);
    }

    .profile-summary { padding: 8px 0; }

    .cat-label {
      display: inline-block;
      padding: 3px 10px;
      border-radius: 20px;
      background: #f4e9de;
      color: var(--brown);
      font-size: 11px;
      font-weight: 700;
    }

    .profile-summary h2 {
      margin: 10px 0 12px;
      color: var(--dark);
      font-size: 34px;
      line-height: 1.3;
    }

    .profile-summary > p {
      color: var(--muted);
      font-size: 14px;
    }

    .profile-info {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 12px;
      margin-top: 20px;
    }

    .info-card {
      padding: 14px;
      border: 1px solid var(--line);
      border-radius: 14px;
      background: white;
    }

    .info-label {
      display: block;
      margin-bottom: 5px;
      color: var(--muted);
      font-size: 12px;
    }

    .info-card strong {
      display: block;
      color: var(--dark);
      font-size: 14px;
    }

    .care-panel {
      margin-top: 26px;
      padding: 22px;
      border: 1px solid #e0e5d7;
      border-radius: 18px;
      background: #eef0e7;
    }

    .care-panel h3 {
      margin: 0 0 8px;
      color: #46563b;
      font-size: 18px;
    }

    .care-panel p {
      margin: 0;
      color: #58634f;
      font-size: 14px;
    }

    #ar-section {
      margin-top: 30px;
      padding: 24px;
      border: 1px solid var(--line);
      border-radius: 22px;
      background: white;
      box-shadow: var(--shadow);
    }

    #ar-section h3 {
      margin: 0;
      color: var(--dark);
      font-size: 23px;
    }

    .hint {
      color: var(--muted);
      font-size: 13px;
      line-height: 1.8;
    }

    model-viewer {
      display: block;
      width: 100%;
      height: 390px;
      margin-top: 16px;
      border-radius: 16px;
      background: #f5eee6;
      --poster-color: #f5eee6;
    }

    .ar-note {
      margin-top: 14px;
      padding: 12px 15px;
      border-radius: 12px;
      background: var(--bg);
    }

    footer {
      padding: 28px 16px;
      border-top: 1px solid var(--line);
      color: var(--muted);
      font-size: 12px;
      text-align: center;
    }

    footer strong {
      color: var(--dark);
      font-size: 15px;
    }

    @media (max-width: 720px) {
      .site-header { padding: 14px 18px; }
      main { padding: 24px 16px 40px; }

      #cat-list {
        grid-template-columns: repeat(2, minmax(0, 1fr));
        gap: 12px;
      }

      .cat-photo { height: 185px; }
      .cat-card { padding: 9px; }
      .cat-card h2 { font-size: 20px; }
      .cat-card p { font-size: 12px; }

      .profile-top {
        grid-template-columns: 1fr;
        gap: 16px;
      }

      #profile-photo { height: 300px; }
      .profile-summary h2 { font-size: 30px; }
      #ar-section { padding: 16px; }
      model-viewer { height: 330px; }
    }

    @media (max-width: 380px) {
      #cat-list { grid-template-columns: 1fr; }
      .cat-photo { height: 230px; }
      .profile-info { grid-template-columns: 1fr; }
      .nav-note { font-size: 11px; }
    }
  </style>
</head>

<body>
  <header class="site-header">
    <nav class="nav">
      <a class="logo" href="./index.html">プレおむ<span>.</span></a>
      <div class="nav-note">ねことの暮らしを、迎える前に。</div>
    </nav>
  </header>

  <main>
    <section id="cat-list-section">
      <div class="page-heading">
        <p class="eyebrow">MEET YOUR CAT</p>
        <h1>猫たちに会ってみよう。</h1>
        <p>気になる猫を選んで、性格や暮らしのポイントを見てみましょう。</p>
      </div>

      <div id="cat-list"></div>
    </section>

    <section id="profile">
      <button class="secondary-button back-button" id="back-button">
        ← 猫たちの一覧に戻る
      </button>

      <div class="profile-top">
        <img id="profile-photo" src="" alt="猫の写真">

        <div class="profile-summary">
          <span class="cat-label">MEET YOUR CAT</span>
          <h2 id="profile-name"></h2>
          <p id="profile-intro"></p>

          <div class="profile-info">
            <div class="info-card">
              <span class="info-label">年齢</span>
              <strong id="profile-age"></strong>
            </div>
            <div class="info-card">
              <span class="info-label">性格</span>
              <strong id="profile-personality"></strong>
            </div>
            <div class="info-card">
              <span class="info-label">好きなこと</span>
              <strong id="profile-likes"></strong>
            </div>
            <div class="info-card">
              <span class="info-label">暮らしのヒント</span>
              <strong>環境を整える</strong>
            </div>
          </div>
        </div>
      </div>

      <section class="care-panel">
        <h3>🐾 一緒に暮らすためのポイント</h3>
        <p id="profile-care"></p>
      </section>

      <section id="ar-section">
        <h3>お部屋で一緒に暮らしてみよう</h3>
        <p class="hint">
          3Dモデルを動かして猫の姿を確認できます。
          対応するスマートフォンでは「AR」ボタンから、
          床などの平らな場所に猫を配置できます。
        </p>

        <model-viewer
          id="cat-model"
          src="./domestic-cat-sitting.glb"
          alt="猫の3Dモデル"
          ar
          ar-modes="webxr scene-viewer quick-look"
          camera-controls
          touch-action="pan-y"
          shadow-intensity="1"
          environment-image="neutral"
          loading="eager">
        </model-viewer>

        <div class="ar-note hint">
          <strong>暮らしを想像してみよう</strong><br>
          猫が過ごすスペースや家具の配置を考えてみましょう。
          実際の性格や行動には個体差があります。
        </div>
      </section>
    </section>
  </main>

  <footer>
    <strong>プレおむ.</strong> — ねこをお家にプレお迎え<br>
    ねことの出会いが、安心できる暮らしにつながりますように。
  </footer>

  <script>
    const cats = [
      {
        name: "ミケ",
        age: "2歳",
        personality: "好奇心旺盛",
        intro: "人と遊ぶことが好きな、好奇心いっぱいの猫です。",
        likes: "おもちゃ遊び・窓の外",
        care: "一緒に遊ぶ時間をつくりましょう。家具などで爪とぎをする場合に備えて、適切な爪とぎ器や安心して過ごせる場所を用意しておくと安心です。",
        image: "./mike.jpg",
        model: "./domestic-cat-sitting.glb"
      },
      {
        name: "ソラ",
        age: "1歳",
        personality: "活発で元気",
        intro: "体を動かすことや、高い場所に登ることが好きな猫です。",
        likes: "走ること・高い場所",
        care: "上下運動ができる場所を用意し、誤飲につながる小物や危険な場所がないか確認しましょう。遊びの時間も大切です。",
        image: "./sora.jpg",
        model: "./domestic-cat-sitting.glb"
      },
      {
        name: "モモ",
        age: "4歳",
        personality: "落ち着いた性格",
        intro: "自分のペースを大切にしながら、ゆっくり過ごすことが好きな猫です。",
        likes: "静かな場所・休息",
        care: "猫がひとりで安心して休める場所を用意しましょう。来客や大きな音があるときも、猫が自分で離れられる環境が大切です。",
        image: "./momo.jpg",
        model: "./domestic-cat-sitting.glb"
      }
    ];

    const catList = document.getElementById("cat-list");
    const listSection = document.getElementById("cat-list-section");
    const profile = document.getElementById("profile");
    const catModel = document.getElementById("cat-model");

    cats.forEach((cat, index) => {
      const card = document.createElement("article");
      card.className = "cat-card";

      const photo = document.createElement("img");
      photo.className = "cat-photo";
      photo.src = cat.image;
      photo.alt = cat.name + "の写真";
      photo.loading = "lazy";

      const content = document.createElement("div");
      content.className = "cat-card-content";

      const name = document.createElement("h2");
      name.textContent = cat.name;

      const personality = document.createElement("p");
      personality.textContent = cat.intro;

      const button = document.createElement("button");
      button.className = "primary-button";
      button.textContent = "プロフィールを見る";
      button.addEventListener("click", () => showProfile(index));

      content.append(name, personality, button);
      card.append(photo, content);
      catList.appendChild(card);
    });

    function showProfile(index) {
      const cat = cats[index];

      document.getElementById("profile-photo").src = cat.image;
      document.getElementById("profile-photo").alt = cat.name + "の写真";
      document.getElementById("profile-name").textContent = cat.name;
      document.getElementById("profile-intro").textContent = cat.intro;
      document.getElementById("profile-age").textContent = cat.age;
      document.getElementById("profile-personality").textContent =
        cat.personality;
      document.getElementById("profile-likes").textContent = cat.likes;
      document.getElementById("profile-care").textContent = cat.care;
      catModel.src = cat.model;

      listSection.style.display = "none";
      profile.style.display = "block";
      window.scrollTo({ top: 0, behavior: "smooth" });
    }

    document.getElementById("back-button").addEventListener("click", () => {
      profile.style.display = "none";
      listSection.style.display = "block";
      window.scrollTo({ top: 0, behavior: "smooth" });
    });
  </script>
</body>
</html>
