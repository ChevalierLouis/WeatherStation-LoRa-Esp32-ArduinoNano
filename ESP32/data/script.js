function onButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "on", true);
    xhttp.send();
}

function offButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "off", true);
    xhttp.send();
}

setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("val1").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "val1", true);
    xhttp.send();
}, 1000);

setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("val2").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "val2", true);
    xhttp.send();
}, 1000);

setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("val3").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "val3", true);
    xhttp.send();
}, 1000);
setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("val4").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "val4", true);
    xhttp.send();
}, 1000);
setInterval(function getData()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if(this.readyState == 4 && this.status == 200)
        {
            document.getElementById("val5").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "val5", true);
    xhttp.send();
}, 1000);