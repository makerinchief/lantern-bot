// TODO: Format this for better readability.

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Lantern Bot</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Monospace;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}

    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}

    .switch {position: relative; display: inline-block; width: 120px; height: 68px}
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
  </style>
</head>
<body>
  <h2>Lantern Bot</h2>
  <label class="switch">
    <input type="checkbox" onchange="toggleCheckbox(this)" id="ledControl">
    <span class="slider"></span>
  </label>
  <script>
    function toggleCheckbox(element) {
      const xhr = new XMLHttpRequest();    
      if(element.checked){
        xhr.open("GET", "/power?state=1", true);
      }
      else {
        xhr.open("GET", "/power?state=0", true);
      }
      xhr.send();
    }
  </script>
</body>
</html>
)rawliteral";
