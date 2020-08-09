var myApp = angular.module("myApp", ['ngRoute']);

myApp.config(function($routeProvider){
    $routeProvider
    .when('/', {
        templateUrl : 'login.html'
    })
    .when('/control', {
        templateUrl : 'control.html'
    })
    .otherwise({
        redirectTo : '/'
    });
});

myApp.controller('loginCtrl', function($scope, $location){
    $scope.submit = function() {
        var usname = $scope.username;
        var pass = $scope.password;
        if($scope.username == 'IndruinoAdmin' && $scope.password == '123456'){
            $location.path('/control');
        } else {
           alert("Failed Login");
        }
    };
});

myApp.controller('ctrller', function($scope, $http){
    $scope.fan = null;
    $scope.light = null;
    $scope.motor = null;
    $scope.control = function() {
        var data = {
            fan: $scope.fan,
            light: $scope.light,
            motor : $scope.motor
        }
        $http.post("https://jsonplaceholder.typicode.com/posts", JSON.stringify(data))
             .then(function(response){
                console.log(response);
             })
    };
});
