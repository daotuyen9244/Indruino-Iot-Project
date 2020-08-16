//var student = { name : "Nguyen Van Cuong", age : "26" };
 
//var student_string = JSON.stringify(student);
 
var persist = require('node-persist');
persist.initSync();
//persist.setItemSync('student', student_string);
 var student_from_file = persist.getItemSync('student');
 console.log(student_from_file);