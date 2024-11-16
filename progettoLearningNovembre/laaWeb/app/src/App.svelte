<script lang="ts">
  const DIVIDENDO:number = 3;


  function calcTotalItemsAfterPromo(quantity:number) {
    const totGruppi: number = roundNumberRibasso(quantity/DIVIDENDO);
    let totItemsDaPagare: number = quantity - (totGruppi*DIVIDENDO);
    totItemsDaPagare += totGruppi * (DIVIDENDO-1);
    return totItemsDaPagare;
  };


  function calcPriceItem(quantity:number, price:number) {
    return price * calcTotalItemsAfterPromo(quantity);
  };


  function roundNumberRibasso(thisFloat:number) {
    for(let i=thisFloat; i>thisFloat-2; i--) {
      console.log(i);
    }
    // const myStringNumber:number = Number(thisFloat.toFixed(1));
    // const decimalNumber:number = myStringNumber[myStringNumber.length-1];
    // let myInt = myStringNumber - (decimalNumber/10);
    // const isCorrect = (thisFloat - myInt) > 0;
    // if(isCorrect) return myInt;
    // return myInt-1;
    // // const myToFixed: number = Number(thisFloat.toFixed(0));
    // // const isCorrect: boolean = (thisFloat - myToFixed) > 0;
    // // if(isCorrect) return myToFixed;
    // // return myToFixed-1;
  };


  console.log(calcPriceItem(20,3));


</script>