document.querySelectorAll("template").forEach((thisTemplateElement) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();

      [["class", "classList"], ["style", "style"]].forEach((thisAttribute) => {
        if (thisTemplateElement.hasAttribute(thisAttribute[0])) {
          console.log(thisAttribute, thisTemplateElement.hasAttribute(thisAttribute[0]));
          this[thisAttribute[1]] = `${
            this[thisAttribute[1]]
          } ${thisTemplateElement.getAttribute(thisAttribute[0])}`.trim();
        }
      });
    }

    // static get observedAttributes() {
    //   const attributesToObserve = [...thisTemplateElement.attributes]
    //     .map((thisAttribute) => thisAttribute.nodeName)
    //     .filter((thisAttribute) => {
    //       const isIdAttribute = thisAttribute === "id";
    //       const isClassAttribute = thisAttribute === "class";
    //       if (isIdAttribute || isClassAttribute) return;
    //       return true;
    //     });
    //   return attributesToObserve;
    // }

    // _connectedCallback() {}
    // _disconnectedCallback() {}
    // /**
    //  * @param {string} attributeName
    //  * @param {any} oldValue
    //  * @param {any} newValue
    //  */
    // _attributeChangedCallback(attributeName, oldValue, newValue) {}

    // connectedCallback() {
    //   this._connectedCallback();
    // }

    // disconnectedCallback() {
    //   this._disconnectedCallback();
    // }
    // /**
    //  * @param {string} attributeName
    //  * @param {any} oldValue
    //  * @param {any} newValue
    //  */
    // attributeChangedCallback(attributeName, oldValue, newValue) {
    //   this._attributeChangedCallback(attributeName, oldValue, newValue);
    // }
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
