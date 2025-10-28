const statusText = document.getElementById("status");
const btnOpen = document.getElementById("open");
const btnClose = document.getElementById("close");
const servoArm = document.getElementById("servoArm");

function sendCommand(cmd) {
  fetch(`/${cmd}`)
    .then(response => response.text())
    .then(result => {
      if (result === "OPENED") {
        statusText.innerHTML = '<span class="status-indicator open"></span>Statut : Barrière ouverte ✅';
        servoArm.style.transform = "translateX(-50%) rotate(90deg)";
      } else if (result === "CLOSED") {
        statusText.innerHTML = '<span class="status-indicator closed"></span>Statut : Barrière fermée ⛔';
        servoArm.style.transform = "translateX(-50%) rotate(0deg)";
      }
    })
    .catch(() => {
      statusText.innerHTML = '<span class="status-indicator"></span>Erreur de communication ❌';
    });
}

btnOpen.addEventListener("click", () => sendCommand("open"));
btnClose.addEventListener("click", () => sendCommand("close"));

setInterval(() => {
  fetch("/status")
    .then(res => res.text())
    .then(state => {
      if (state === "OPEN") {
        statusText.innerHTML = '<span class="status-indicator open"></span>Statut : Barrière ouverte ✅';
        servoArm.style.transform = "translateX(-50%) rotate(90deg)";
      } else {
        statusText.innerHTML = '<span class="status-indicator closed"></span>Statut : Barrière fermée ⛔';
        servoArm.style.transform = "translateX(-50%) rotate(0deg)";
      }
    });
}, 5000);
