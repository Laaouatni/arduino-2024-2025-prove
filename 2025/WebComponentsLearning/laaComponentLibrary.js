document.querySelectorAll("template").forEach((template) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();
      const shadow = this.attachShadow({ mode: "open" });
      shadow.appendChild(template.content.cloneNode(true));
    }
    /**
     * 
     * @param {String} attributeName 
     * @param {String} oldValue 
     * @param {String} newValue 
     */
    attributeChangedCallback(attributeName, oldValue, newValue) {
      console.log({ attributeName, oldValue, newValue });
    }
  }
  customElements.define(template.id, ThisComponent);
});
