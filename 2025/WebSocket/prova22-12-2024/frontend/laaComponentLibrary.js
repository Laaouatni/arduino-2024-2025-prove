document.querySelectorAll("template").forEach((thisTemplateElement) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();

      ["class", "style"].forEach((thisAttributeName) => {
        if (thisTemplateElement.hasAttribute(thisAttributeName)) {
          this.setAttribute(
            thisAttributeName,
            `${
              this.getAttribute(thisAttributeName) || ""
            } ${thisTemplateElement.getAttribute(thisAttributeName)}`.trim(),
          );
        }
      });

      const allScriptElementsInsideTemplate = thisTemplateElement.content.querySelectorAll("script");
      allScriptElementsInsideTemplate.forEach((thisScriptTemplateElement) => {
        const generatedScriptElementInsideComponent = document.createElement("script");
        generatedScriptElementInsideComponent.textContent = isolateScriptStringInsideComponent(
          thisScriptTemplateElement.textContent || ""
        )
        this.appendChild(generatedScriptElementInsideComponent);
      });
    }

    static get observedAttributes() {
      const attributesToObserve = [...thisTemplateElement.attributes]
        .map((thisAttribute) => thisAttribute.nodeName)
        .filter((thisAttribute) => {
          let canSkip = false;
          ["id", "class"].forEach((thisAttributeName) => {
            if (thisAttribute == thisAttributeName) canSkip = true;
          });
          return !canSkip;
        });
      return attributesToObserve;
    }

    _connectedCallback() {}
    _disconnectedCallback() {}
    /**
     * @param {string} attributeName
     * @param {any} oldValue
     * @param {any} newValue
     */
    _attributeChangedCallback(attributeName, oldValue, newValue) {}

    connectedCallback() {
      this._connectedCallback();
    }

    disconnectedCallback() {
      this._disconnectedCallback();
    }
    /**
     * @param {string} attributeName
     * @param {any} oldValue
     * @param {any} newValue
     */
    attributeChangedCallback(attributeName, oldValue, newValue) {
      this._attributeChangedCallback(attributeName, oldValue, newValue);
    }
  }

  customElements.define(thisTemplateElement.id, ThisComponent);
});

/**
 * @param   {string} thisScriptString
 * @returns {string}
 */
function isolateScriptStringInsideComponent(thisScriptString) {
  return `(()=>{
    const thisComponent = document.currentScript.parentElement;
    ${thisScriptString}}
  )()`;
}
