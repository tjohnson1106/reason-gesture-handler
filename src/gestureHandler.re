open BsReactNative;

type coordinates = {
  x: float,
  y: float,
};

type state = {
  pan: Animated.ValueXY.t,
  childCoordinates: ref(Animated.ValueXY.jsValue),
};

let component = ReasonReact.reducerComponent("GestureHandler");

/* ...children needs spread operator because Reason parses the jsx
   'children' and that translates to ([|childred|])   */

let make = children => {
  ...component,
  initialState: () => {
    pan: Animated.ValueXY.create(~x=0., ~y=0.),
    childCoordinates: ref({"x": 0., "y": 0.}),
  },
  reducer: ((), _state: state) => ReasonReact.NoUpdate,
  render: _self => <View> <Animated.View> ...children </Animated.View> </View>,
};