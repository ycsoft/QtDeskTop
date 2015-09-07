// JavaScript Document
//改变对象的背景颜色
var cur = 0;
var colMax = 4;

var curRow = 1;
var curCol = 3;

function mouseIn( obj )
{
//	var elem = document.getElementById("all");
	obj.style.backgroundColor = "#666666"; 
}
function mouseOut(obj)
{
	obj.style.backgroundColor = "#2F2F2F"; 
}
function clickTask(txt)
{
	alert(txt.innerHTML);	
}

//添加一件事项
function addTask()
{
	
	if ( curCol < colMax)
	{
	var listElem = document.getElementById('row');
	var lastElem = listElem.nextSibling;
	if( curRow  > 1)
	{
		while(lastElem != undefined)
		{
			listElem = lastElem;
			lastElem = lastElem.nextSibling;
		}
	}
	var curText = listElem.innerHTML;
	curText = curText + 
"<div class=\"listtext\">"+
"<div class=\"block-left\" onclick=\"clickTask(this)\">"+
"121312312321313124334353453454365465467fsdfsfsfsdfsfasfsafasnifhadfoasdnfowefjqofnasldfnlaksdfnoiefnaslkdf"+
"</div>"+
"<div class=\"block-right\"> <hr class=\"vertical\" /></div>"+
"</div>";
curCol += 1;
listElem.innerHTML = curText;
	}else{
		curCol = 1;
			var elemContent = document.getElementById('content');
			
			curText = elemContent.innerHTML + 
			"<hr /><div class=\"row\" id=\"row\">"+
"<div class=\"listtext\">"+
"<div class=\"block-left\" onclick=\"clickTask(this)\">"+
"121312312321313124334353453454365465467fsdfsfsfsdfsfasfsafasnifhadfoasdnfowefjqofnasldfnlaksdfnoiefnaslkdf"+
"</div>"+
"<div class=\"block-right\"> <hr class=\"vertical\" /></div>"+
"</div></div>";
elemContent.innerHTML = curText;
curRow += 1;
	}
	
}

function listList( obj )
{
	
}
