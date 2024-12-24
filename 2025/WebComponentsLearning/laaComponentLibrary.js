document.querySelectorAll("template").forEach((template) => {
  class ThisComponent extends HTMLElement {
    constructor() {
      super();
      let shadow = this.attachShadow({ mode: "open" });
      shadow.appendChild(template.content.cloneNode(true));
    }

    static get observedAttributes() {
      const attributesToObserve = [...template.attributes].filter((thisAttribute) => {
        const isIdAttribute = thisAttribute.nodeName === "id";
        if (isIdAttribute) return;
        return thisAttribute.nodeName;
      });
      console.log(attributesToObserve);
      return ["checked"];
    }

    attributeChangedCallback(attributeName, oldValue, newValue) {
      // console.log({ attributeName, oldValue, newValue });
    }
  }
  customElements.define(template.id, ThisComponent);
});