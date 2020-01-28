import binary from 'node-pre-gyp';
import path from 'path';

const bindingPath = binary.find(path.resolve(__dirname, '../package.json'));
const oldPath = process.cwd();

process.chdir(path.dirname(bindingPath));
const addon = require(bindingPath);

process.chdir(oldPath);

export type Menu = {
  text: string;
  disabled: boolean;
  checked: boolean;

  callback: (menu: Menu, context?: any) => void;

  submenu?: Menu;
};

export type Tray = {
  iconPath?: string;
  menu: Menu;
};

class SystemTray {
  constructor(private config: Tray) {}

  start() {
    addon.start(this.config);
  }

  stop() {
    addon.stop();
  }
}

let systemTray: SystemTray = undefined;

export const createTray = (config: Tray) => {
  if (systemTray !== undefined) {
    systemTray.stop();
  }

  systemTray = new SystemTray(config);

  systemTray.start();
};

export const destroyTray = () => {
  systemTray.stop();
};
