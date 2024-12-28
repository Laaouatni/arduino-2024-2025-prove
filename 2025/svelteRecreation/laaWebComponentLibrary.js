document.querySelectorAll("template").forEach((thisTemplateElement) => {
  class ThisComponent extends HTMLElement {
    /**
     * @type {ShadowRoot}
     */
    shadowDom;

    /**
     *
     * @type {{[variableName:string]: any}}
     */
    stateVariables = {};
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

      this.stateVariables = new Proxy(this.stateVariables, {
        set: (parent, child, val) => {
          parent[child] = val;
          // console.log({child, val})
          updateComponentInnerHtmlVariables(this);
          return true;
        },
      });

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

  /**
   *
   * @param {ThisComponent} thisComponent
   */
  function updateComponentInnerHtmlVariables(thisComponent) {
    // console.log(thisComponent.stateVariables)
    thisComponent.shadowDom.innerHTML =
      replaceHtmlStringVariablesBracketsWithValues(thisComponent);
  }

  /**
   *
   * @param {string} htmlStringToMinify
   * @returns {string}
   */
  function minifyHtmlString(htmlStringToMinify) {
    return htmlStringToMinify.replaceAll("\n", "").replaceAll("  ", "");
  }

  /**
   *
   * @param {ThisComponent} thisComponent
   * @returns {string}
   */
  function replaceSlotTagWithSlotContent(thisComponent) {
    const minifiedHtmlStrings = {
      shadowDom: minifyHtmlString(thisTemplateElement.innerHTML),
      slot: minifyHtmlString(thisComponent.innerHTML),
    };
    const regexScriptTag = /<script>.*<\/script>/g;
    const slotHtmlStringWithoutScripts = minifiedHtmlStrings.slot.replace(
      regexScriptTag,
      "",
    );
    return minifiedHtmlStrings.shadowDom.replaceAll(
      "<slot></slot>",
      slotHtmlStringWithoutScripts,
    );
  }

  /**
   *
   * @param {ThisComponent} thisComponent
   * @returns {string}
   */
  function replaceHtmlStringVariablesBracketsWithValues(thisComponent) {
    const thisComponentHtmlWithSlotTagReplacedWithSlotContent =
      replaceSlotTagWithSlotContent(thisComponent);
    const regexGetAllVariableBracketsInString = /\{.[^}]*\}/g;
    // console.log({ replaceHtml: thisComponentHtmlWithSlotTagReplacedWithSlotContent })

    return thisComponentHtmlWithSlotTagReplacedWithSlotContent.replace(
      regexGetAllVariableBracketsInString,
      (thisVariableBracketStringPart) => {
        const variableName = thisVariableBracketStringPart.replace(
          /\{|\}/g,
          "",
        );
        return thisComponent.stateVariables[variableName];
      },
    );
  }

  function copyTemplateContentToComponentShadowDom() {
    this.shadowDom = this.attachShadow({ mode: "open" });
    const clonedTemplateContent = thisTemplateElement.content.cloneNode(true);

    clonedTemplateContent.childNodes.forEach((thisChild) => {
      if (thisChild instanceof HTMLScriptElement) thisChild.remove();
    });

    this.shadowDom.appendChild(clonedTemplateContent);
  }

  /**
   *
   * @param {string[]} attributesToCopyArray
   */
  function copyAttributesFromTemplateToComponent(attributesToCopyArray) {
    attributesToCopyArray.forEach((thisAttributeName) => {
      if (!thisTemplateElement.hasAttribute(thisAttributeName)) return;

      this.setAttribute(
        thisAttributeName,
        `${
          this.getAttribute(thisAttributeName) || ""
        } ${thisTemplateElement.getAttribute(thisAttributeName)}`.trim(),
      );
    });
  }

  function copyScriptsFromTemplateToComponent() {
    const allScriptElementsInsideTemplate =
      thisTemplateElement.content.querySelectorAll("script");

    const generatedScriptElementInsideComponent =
      document.createElement("script");

    const mergedScriptTags = [...allScriptElementsInsideTemplate]
      .map((thisScriptTemplateElement) => {
        if (!thisScriptTemplateElement.textContent) return "";
        return thisScriptTemplateElement.textContent;
      })
      .join("");

    generatedScriptElementInsideComponent.textContent =
      isolateScriptStringInsideComponent(mergedScriptTags).replaceAll("  ", "");

    this.appendChild(generatedScriptElementInsideComponent);
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
