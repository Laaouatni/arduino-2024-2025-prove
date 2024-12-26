document.querySelectorAll("template").forEach((thisTemplateElement) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();
    }

    static get observedAttributes() {
      const attributesToObserve = [...thisTemplateElement.attributes]
        .map((thisAttribute) => thisAttribute.nodeName)
        .filter((thisAttribute) => {
          let canSkip = false;
          ["id", "class", "style"].forEach((thisAttributeName) => {
            if (thisAttribute == thisAttributeName) canSkip = true;
          });
          return !canSkip;
        });
      return attributesToObserve;
    }

    _connectedCallback() {}
    connectedCallback() {
      this._connectedCallback();

      const copyFromTemplateToComponent = {
        templateContent: copyTemplateContentToComponentShadowDom.bind(this),
        attributes: copyAttributesFromTemplateToComponent.bind(this),
        scripts: copyScriptsFromTemplateToComponent.bind(this),
      };

      copyFromTemplateToComponent.templateContent();
      copyFromTemplateToComponent.attributes(["class", "style"]);
      copyFromTemplateToComponent.scripts();
    }

    _disconnectedCallback() {}
    disconnectedCallback() {
      this._disconnectedCallback();
    }

    /**
     * @param {string} attributeName
     * @param {any} oldValue
     * @param {any} newValue
     */
    _attributeChangedCallback(attributeName, oldValue, newValue) {}
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

  function copyTemplateContentToComponentShadowDom() {
    const thisShadowDom = this.attachShadow({ mode: "open" });
    const clonedTemplateContent = thisTemplateElement.content.cloneNode(true);

    clonedTemplateContent.childNodes.forEach((thisChild) => {
      if (thisChild instanceof HTMLScriptElement) thisChild.remove();
    });

    thisShadowDom.appendChild(clonedTemplateContent);
  }

  /**
   *
   * @param {string[]} attributesToCopyArray
   */
  function copyAttributesFromTemplateToComponent(attributesToCopyArray) {
    attributesToCopyArray.forEach((thisAttributeName) => {
      if (thisTemplateElement.hasAttribute(thisAttributeName)) {
        this.setAttribute(
          thisAttributeName,
          `${
            this.getAttribute(thisAttributeName) || ""
          } ${thisTemplateElement.getAttribute(thisAttributeName)}`.trim(),
        );
      }
    });
  }

  function copyScriptsFromTemplateToComponent() {
    const allScriptElementsInsideTemplate =
      thisTemplateElement.content.querySelectorAll("script");

    allScriptElementsInsideTemplate.forEach((thisScriptTemplateElement) => {
      const generatedScriptElementInsideComponent =
        document.createElement("script");
      generatedScriptElementInsideComponent.textContent =
        isolateScriptStringInsideComponent(
          thisScriptTemplateElement.textContent || "",
        );
      this.appendChild(generatedScriptElementInsideComponent);
    });
  }

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
});
