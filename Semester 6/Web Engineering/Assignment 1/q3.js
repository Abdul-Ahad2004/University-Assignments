const students = [
    { name: "Ali", age: 22, marks: 85 },
    { name: "Ayesha", age: 20, marks: 92 },
    { name: "Bilal", age: 23, marks: 78 },
    { name: "Ibrahim", age: 22, marks: 76 },
    { name: "Usama", age: 21, marks: 80 }
];

const sortByMarksDescending = (arr) => {
    return arr.sort((a, b) => b.marks - a.marks);
};

console.log("Sorted by Marks (Descending):", sortByMarksDescending([...students]));

const getTopStudents = (arr) => {
    return arr.filter(student => student.marks > 80).map(student => student.name);
};

console.log("Students with marks > 80:", getTopStudents(students));

const getOlderStudents = (arr) => {
    return arr.filter(student => student.age > 21);
};

console.log("Students older than 21:", getOlderStudents(students));
