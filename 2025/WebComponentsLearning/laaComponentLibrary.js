document.querySelectorAll("template").forEach((thisTemplateElement) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();
      let shadow = this.attachShadow({ mode: "open" });
      shadow.appendChild(thisTemplateElement.content.cloneNode(true));

      const hasScriptTag = thisTemplateElement.content.querySelector("script");
      if (hasScriptTag) {
        const generatedShadowScript = document.createElement("script");
        generatedShadowScript.textContent = hasScriptTag.textContent;
        shadow.host.appendChild(generatedShadowScript);
      }
    }

    static get observedAttributes() {
      const attributesToObserve = [...thisTemplateElement.attributes].filter((thisAttribute) => {
        const isIdAttribute = thisAttribute.nodeName === "id";
        if (isIdAttribute) return;
        return thisAttribute.nodeName;
      });
      return ["checked"];
    }

    // _attributeChangedCallback(attributeName, oldValue, newValue) {
    // };

    attributeChangedCallback(attributeName, oldValue, newValue) {
      // console.log(`Attribute: ${attributeName} changed from ${oldValue} to ${newValue}`);
      this._attributeChangedCallback(attributeName, oldValue, newValue);
    }
  }
  customElements.define(thisTemplateElement.id, ThisComponent);
});