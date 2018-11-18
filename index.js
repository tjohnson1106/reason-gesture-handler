/** @format */

import { AppRegistry } from "react-native";
import App from "./lib/js/src/app.bs.js";
import { name as appName } from "./app.json";

AppRegistry.registerComponent(appName, () => App);
