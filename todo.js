var i=0;
var nextentry;
function addinlist()
{
    var ttl=document.getElementById("title").value;
    // var desc=document.getElementById("discribe").value;

    
    var newtask=document.createElement("div");
    newtask.id="arr["+i+"]";
    newtask.className="todo";
    newtask.innerHTML="<p class='task' id='h"+i+"'>"+ttl+"</p><button class='submit'id="+i+" onclick='remove(this.id)'>Completed</button>";
    
    
    
    nextentry=document.getElementById("todolist");
    
    nextentry.appendChild(newtask);    
    i+=1;
}

function remove(c_id)
{
    var dummy="arr["+c_id+"]";
    var idd=document.getElementById(dummy);
    nextentry.removeChild(idd);

}

function reset()
{
    document.getElementById("title").value="";
}




