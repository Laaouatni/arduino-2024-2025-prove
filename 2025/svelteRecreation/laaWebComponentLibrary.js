document.querySelectorAll("template").forEach((thisTemplateElement) => {
  class ThisComponent extends HTMLElement {
    /**
     * @type {ShadowRoot}
     */
    shadowDom;
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

      updateInnerHtmlVariables(this);

      /**
       *
       * @param {ThisComponent} thisComponent
       */
      function updateInnerHtmlVariables(thisComponent) {
        const shadowDomStringMinified = minifyString(
          thisComponent.shadowDom.innerHTML,
        );

        const splittedShadowDomString = splitUsingVariablesAsDeliminator(
          shadowDomStringMinified,
        );

        const splittedShadowDomStringWithSlotReplaced =
          splitUsingVariablesAsDeliminator(
            splitShadowDomStringWithSlotReplaced(splittedShadowDomString).join(
              "",
            ),
          );
        let n = 8;
        let a = 19;
        let aaaa = "valore aaaa";

        const splittedShadowDomStringWithValues =
          splitShadowDomStringWithValues(
            splitUsingVariablesAsDeliminator(
              minifyString(splittedShadowDomStringWithSlotReplaced.join("")),
            ),
          );

        replaceShadowDomComponentWithNewValues();

        /**
         *
         * @param {string} stringToMinify
         * @returns {string}
         */
        function minifyString(stringToMinify) {
          return stringToMinify.replaceAll("\n", "").replaceAll("  ", "");
        }

        /**
         *
         * @param {string} parameterString
         * @returns {string[]}
         */
        function splitUsingVariablesAsDeliminator(parameterString) {
          const regexGetAllVariableInInnerHTML = /({[^}]*})/g;
          return parameterString.split(regexGetAllVariableInInnerHTML);
        }

        /**
         *
         * @param {string[]} parameterStringArray
         * @returns {string[]}
         */
        function splitShadowDomStringWithSlotReplaced(parameterStringArray) {
          return [...parameterStringArray]
            .map((thisString) => {
              const isStringIncludesSlot = thisString.includes("slot");
              if (!isStringIncludesSlot) return thisString;
              return returnModifiedSlotString();

              function returnModifiedSlotString() {
                let slotWantedElementsArray = [];

                thisComponent.childNodes.forEach((thisChild) => {
                  if (thisChild instanceof HTMLScriptElement) return;
                  if (thisChild instanceof Text) {
                    slotWantedElementsArray.push(thisChild.nodeValue);
                    return;
                  }
                  slotWantedElementsArray.push(
                    `<${thisChild.nodeName.toLocaleLowerCase()}>
                      ${thisChild.innerHTML}
                     </${thisChild.nodeName.toLocaleLowerCase()}>`,
                  );
                });

                return slotWantedElementsArray.join("");
              }
            })
            .flat();
        }

        function splitShadowDomStringWithValues(parameterStringArray) {
          return [...parameterStringArray].map((thisString) => {
            const isThisStringVariableType =
              thisString.startsWith("{") && thisString.endsWith("}");
            if (!isThisStringVariableType) return thisString;

            const thisVariableName = thisString
              .replace("{", "")
              .replace("}", "");
            return eval(thisVariableName);
          });
        }

        function replaceShadowDomComponentWithNewValues() {
          thisComponent.shadowDom.innerHTML =
            splittedShadowDomStringWithValues.join("");
        }
      }
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

    const generatedScriptElementInsideComponent =
      document.createElement("script");

    generatedScriptElementInsideComponent.textContent =
      isolateScriptStringInsideComponent(
        [...allScriptElementsInsideTemplate]
          .map((thisScriptTemplateElement) => {
            if (!thisScriptTemplateElement.textContent) return "";
            return thisScriptTemplateElement.textContent.replaceAll("  ", "");
          })
          .join(""),
      );
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
