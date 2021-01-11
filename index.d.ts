declare class Shout {
    setHost(host: string): void;
    setProtocol(protocol: number): void;
    setPort(port: number): void;
    setMount(mount: string): void;
    setPassword(password: string): void;
    setFormat(format: number): void;
    setUser(user: string): void;
    send(buffer: ArrayBuffer): void;
    sync(): void;
    open(): void;
    close(): void;
}

export default Shout;