export class PriorityQueue<T> {
  constructor(priority: (value: T) => number);

  empty(): boolean;
  size(): number;
  push(...vals: T[]): void;
  top(): T | undefined;
  pop(): boolean;
}
