export class PriorityQueue<T extends {}> {
  constructor(priority: (value: T) => number);

  empty(): boolean;
  size(): number;
  push(...vals: T[]): void;
  top(): T | undefined;
  pop(): boolean;
}
