const statusText = document.getElementById("status");
const btnOpen = document.getElementById("open");
const btnClose = document.getElementById("close");
const servoArm = document.getElementById("servoArm");

// Fonction pour envoyer une commande à l’ESP32
function sendCommand(cmd) {
  fetch(`/${cmd}`)
    .then(response => response.text())
    .then(result => {
      if (result === "OPENED") {
        statusText.textContent = "Statut : Barrière ouverte ✅";
        servoArm.style.transform = "rotate(90deg)"; // animation
      } else if (result === "CLOSED") {
        statusText.textContent = "Statut : Barrière fermée ⛔";
        servoArm.style.transform = "rotate(0deg)"; // animation
      }
    })
    .catch(err => {
      statusText.textContent = "Erreur de communication ❌";
    });
}

// Actions des boutons
btnOpen.addEventListener("click", () => sendCommand("open"));
btnClose.addEventListener("click", () => sendCommand("close"));

// Vérification du statut toutes les 5 secondes
setInterval(() => {
  fetch("/status")
    .then(res => res.text())
    .then(state => {
      if (state === "OPEN") {
        statusText.textContent = "Statut : Barrière ouverte ✅";
        servoArm.style.transform = "rotate(90deg)";
      } else {
        statusText.textContent = "Statut : Barrière fermée ⛔";
        servoArm.style.transform = "rotate(0deg)";
      }
    });
}, 5000);
