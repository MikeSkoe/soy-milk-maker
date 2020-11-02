open Reprocessing;

let draw = (state: State.t, env) => {
    let moneyText = "money: " ++ (state.money |> string_of_int);

    Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
    Draw.fill(Constants.black, env);
    Draw.text(~body=moneyText, ~pos=(10, 10), env);

    state;
}

let keyPressed = (state, env) => switch (Env.keyCode(env)) {
  | R => Reducer.reducer(state, Restart)
  | _ => state
}