# shou-t

### Installation

```
yarn add libshout
```

### Usage

```ts
import {Shout} from 'libshout';

async function run() {
    const shout = new Shout();
    
    shout.setHost('127.0.0.1');
    shout.setProtocol(0);
    shout.setPort(8000);
    shout.setPassword('hackme');
    shout.setMount('/example.ogg');
    shout.setUser('source');
    shout.setFormat(0);
    shout.open();
    
    const fd = await fs.promises.open(path.resolve(__dirname,'audio.ogg'), 'r');
    const tmp = Buffer.allocUnsafe(1024 * 4);
    
    while(1) {
        const {bytesRead} = await fd.read(tmp, 0, tmp.byteLength, null);
        if(bytesRead) {
            shout.send(tmp.buffer.slice(0, bytesRead));
        } else {
            break;
        }
        shout.sync();
    }
    shout.close();
}
```
