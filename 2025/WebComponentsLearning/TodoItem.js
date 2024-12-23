document.querySelectorAll("template").forEach((template) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();
      const shadow = this.attachShadow({ mode: "open" });
      shadow.appendChild(template.content.cloneNode(true));
    }
  }
  customElements.define(template.id, ThisComponent);
});


// class TodoItem extends HTMLElement {
//   constructor() {
//     super();
//     const shadow = this.attachShadow({ mode: "open" });
//     shadow.appendChild(document.getElementById("template-ciao").content.cloneNode(true));
//   }
// }

// customElements.define("todo-item", TodoItem);
