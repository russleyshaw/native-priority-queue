import { PriorityQueue } from "./";

function showMeta<T>(pq: PriorityQueue<T>) {
  console.log("Size: ", pq.size());
  console.log("Empty: ", pq.empty());
  console.log("Top: ", pq.top());
}

function pushValue<T>(pq: PriorityQueue<T>, val: T) {
  console.log("Pushing: ", val);
  pq.push(val);
}

const pq = new PriorityQueue<number>();
showMeta(pq);
pushValue(pq, 5);
showMeta(pq);
