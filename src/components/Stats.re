open Reprocessing;

let draw = (env, gameState: State.gameState) => {
   let moneyText = "money: " ++ (gameState.money |> string_of_int);

   Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
   Draw.fill(Constants.black, env);
   Draw.text(~body=moneyText, ~pos=(10, 10), env);
};
