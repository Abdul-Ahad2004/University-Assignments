function processArray(arr, callback) {
    return arr.map(callback);
}

const double = num => num * 2;

const square = num => num * num;

const numbers = [2, 4, 6, 8, 10];

console.log("Proceesed array with double callback: ",processArray(numbers, double)); 
console.log("Proceesed array with square callback: ",processArray(numbers, square)); 
