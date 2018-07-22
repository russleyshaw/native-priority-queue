export class PriorityQueue<T> {
  constructor();

  empty(): boolean;
  size(): number;
  push(...vals: T[]): void;
  top(): T | undefined;
  pop(): boolean;
}
