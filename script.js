document.getElementById("joinForm").addEventListener("submit", e => {
  e.preventDefault();
  alert("🎬 Welcome to Cinemania!");
  e.target.reset();
});
