const darkMode = document.getElementById('dark-mode')
const lightMode = document.getElementById('light-mode')

darkMode.addEventListener('click',()=>{
    document.body.classList.toggle('dark_mode')
})