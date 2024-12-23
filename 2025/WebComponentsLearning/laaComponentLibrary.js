document.querySelectorAll("template").forEach((template) => {
  class ThisComponent extends HTMLElement {
    shadow;
  
    constructor() {
      super();
      this.shadow = this.attachShadow({ mode: "open" });
      this.shadow.appendChild(template.content.cloneNode(true));
    }

    static get observedAttributes() {
      console.log(this.shadow);
      return ["checked"];
    }

    attributeChangedCallback(attributeName, oldValue, newValue) {
      // console.log({ attributeName, oldValue, newValue });
    }
  }
  customElements.define(template.id, ThisComponent);
});
