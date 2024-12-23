document.querySelectorAll("template").forEach((template) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();
      const shadow = this.attachShadow({ mode: "open" });
      shadow.appendChild(template.content.cloneNode(true));

      // Execute custom logic from the <script> tag inside the template
      const script = shadow.querySelector("script");
      if (script) {
        const customLogic = new Function(
          "attributeChangedAttributes",
          script.textContent
        );
        customLogic.call(this, this._setupCustomAttributeCallback.bind(this));
      }
    }
    
    static get observedAttributes() {
      // Dynamically build observed attributes from the template's attributes
      return [...template.attributes]
      .map((attr) => attr.nodeName)
      .filter((attrName) => attrName !== "id");
    }
    
    _setupCustomAttributeCallback(callback) {
      this._customAttributeCallback = callback;
    }
    
    attributeChangedCallback(attributeName, oldValue, newValue) {
      console.log(this._customAttributeCallback);
      if (this._customAttributeCallback) {
        this._customAttributeCallback(attributeName, oldValue, newValue);
      }
    }
  }

  // Define the custom element
  customElements.define(template.id, ThisComponent);
});
