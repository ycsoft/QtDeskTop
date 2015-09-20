// JavaScript Document
//改变对象的背景颜色

var colMax = 5;

var curRow = 0;
var curCol = 0;

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
function addTask(txt)
{
	var content = $("#content");
	var html = content.html();
	
	html += "<dia class='item'>" +txt + "</div>";
	content.html( html );
	
}
//添加一件事项
function addTask2(txt)
{
	
	var test = txt;//"<h3>项目支出明细</h3><p>单位：国库处</p><p>审核：张三</p><p>摘要:2014年度总共支付543万元，其中....</p>";
	if ( curCol < colMax && curRow > 0)
	{
		if( curRow  >= 1)
		{
			var listElem = document.getElementById('row');
			var lastElem = listElem.nextSibling;
			if( curRow > 1)
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
			"<div class=\"block-left\" onclick=\"clickTask(this)\" onmousemove=\"taskMouseIn(this)\" onmouseout=\"taskMouseOut(this)\">"+
			test+
			"</div>"+
			"<div class=\"block-right\"> <hr class=\"vertical\" /></div>"+
			"</div>";
			curCol += 1;
			listElem.innerHTML = curText;
		}
	}else{
		curCol = 1;
		var elemContent = document.getElementById('content');
			
		curText = elemContent.innerHTML + 
		"<hr class=\"hor\" align=\"center\"/><div class=\"row\" id=\"row\">"+
		"<div class=\"listtext\">"+
		"<div class=\"block-left\" onclick=\"clickTask(this)\" onmousemove=\"taskMouseIn(this)\" onmouseout=\"taskMouseOut(this)\">"+
		test+
		"</div>"+
		"<div class=\"block-right\"> <hr class=\"vertical\" /></div>"+
		"</div></div>";
		elemContent.innerHTML = curText;
		curRow += 1;
	}
	
}
function taskMouseIn(obj)
{
	bgstyle = obj.style.backgroundColor;
	obj.style.backgroundColor = "#8080FF"; 
}
function taskMouseOut(obj)
{
	obj.style.backgroundColor = "#D4D4D4";
}

function runQt()
{
	var s = QSimpleMode.invoke();
	alert(s);
}
function reback()
{
	QSimpleMode.returnToAll();
}

function  cfunc_get(sql)
{
	var res = QSimpleMode.get(sql);
	return res;
}

function showMenu()
{
	var pop = window.createPopup();
	//alert(pop);
	  pop.document.oncontextmenu=function(){
                      return false;};
	  pop.show(event.clientX-1,event.clientY,200,2,document.body);
				
}