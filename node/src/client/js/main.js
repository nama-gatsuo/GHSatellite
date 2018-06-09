var onTouch = e => {
    e.preventDefault();
    e.currentTarget.classList.toggle('active');
}

var init = () => {
    let items = document.getElementsByClassName("item");

    for (let i = 0; i < items.length; i++) {
        items[i].addEventListener('touchstart', onTouch, true);
        items[i].classList.add('active');
    }
}

init();
