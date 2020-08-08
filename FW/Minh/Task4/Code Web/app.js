var myApp = angular.module("myApp", ['ngRoute']);

myApp.config(function($routeProvider){
    $routeProvider
    .when('/', {
        templateUrl : 'login.html'
    })
    .when('/dashboard', {
        templateUrl : 'dashboard.html'
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
            $location.path('/dashboard');
        } else {
            alert("Failed Login");
        }
    };
});