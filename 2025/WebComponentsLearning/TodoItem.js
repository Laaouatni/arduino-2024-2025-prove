class TodoItem extends HTMLElement {
  constructor() {
    super();
    this.innerHTML = `Hi I am custom <h3>${this.innerText}</h3>!`;
  }
}

customElements.define("todo-item", TodoItem);
