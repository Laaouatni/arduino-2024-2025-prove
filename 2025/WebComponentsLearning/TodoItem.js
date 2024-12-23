class TodoItem extends HTMLElement {
  constructor() {
    super();
    this.innerHTML = `Hi I am custom ${this.innerText}!`;
  }
}

customElements.define("todo-item", TodoItem);