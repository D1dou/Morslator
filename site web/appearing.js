const header = document.querySelector("header");

let sr = ScrollReveal({
    duration: 2500,
    distance: "60px",
});
sr.reveal(".showcase-info",{delay: 100});
sr.reveal(".showcase-image",{origin:"top", delay: 700});