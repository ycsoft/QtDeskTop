// JavaScript Document
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
	//$('.debug').debug('addTask');
	var content = $(".content");
	var html = content.html();
	var txt = translate2txt(txt);
	//$('.debug').debug(txt);
	
	html += "<div class='item'>"+ '<div>' + txt + '</div>' + "<a class='itembutton' href='#'><img src='img/dwzw.png' class='applyimg' />申请处理</a>"+"</div>";
	content.html( html );
 $('.item').mouseover(function(e) {
     	var itm = $(this);
		var btn = itm.children("a");
		btn.css('display','block');
});
 $('.item').mouseout(function(e) {
     	var itm = $(this);
		var btn = itm.children("a");
		btn.css('display','none');
});

$('.content').find('a').click(function(e) {
    todoNum += 1;
	var txt = $(this).parent("div").children("div").html();
	$('#headtodo').setNumber(todoNum);
	$('.content-todo').addToDo(txt,'处理发送');
	//$('a').addToDo(txt,todoNum);
});	
	//$('.debug').debug('addTask Over');
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
$.fn.extend({
    setNumber:function(count){
			var numstr = $(this).attr('title') + '<div class="number">' +'<img src="img/numback.png" /><div id="number">'+ count + '	</div></div>';
			$(this).html(numstr);
			var snum = count.toString().length - 1;
			var sr = parseInt(20-snum*2);
			$('#number').css('right',sr);
			if ( count <= 0){
				$(this).find('img').css("display","none");	
				$(this).find('div#number').css("display","none");	
			}
		}	
	
});

$.fn.extend({
	addItem:function (txt,btnname){
	var numstr = $(this).html();
			numstr += "<div class='item'><div>" + txt + "</div><a class='itembutton' href='#'><img src='img/dwzw.png' class='applyimg' />"+btnname+"</a></div>";
			
			$(this).html(numstr);
			
			 $('.item').mouseover(function(e) {
     		var itm = $(this);
			var btn = itm.children("a");
				btn.css('display','block');
			});
			$('.item').mouseout(function(e) {
     		var itm = $(this);
			var btn = itm.children("a");
				btn.css('display','none');
			});
			if (btnname != '处理发送')
			{
				$(this).find('a').click(function(e) {
                	$(this).parent('div').css("display","none");
					if( btnname == '删除'){
						done -= 1;
						$('#headdone').setNumber(done);
						}
            	});
			}
		}
	
});

$.fn.extend({
	addToDo: function (txt,btnname){
		/*
			var numstr = $('.content-todo').html();
			numstr += "<div class='item'><div>" + txt + "</div><a class='itembutton' href='#'><img src='img/dwzw.png' class='applyimg' />处理发送</a></div>";
			$('.content-todo').html(numstr);
			
			 $('.item').mouseover(function(e) {
     		var itm = $(this);
			var btn = itm.children("a");
				btn.css('display','block');
			});
			$('.item').mouseout(function(e) {
     		var itm = $(this);
			var btn = itm.children("a");
				btn.css('display','none');
			});*/
			$(this).addItem(txt,btnname);
			
			$('.content-todo').find('a').click(function(e) {
                var itm = $(this).parent("div");
				itm.css("display","none");
				todoNum -= 1;
				done += 1;
				if ( todoNum < 0)
				{
					todoNum = 0;
				}
				$('#headtodo').setNumber(todoNum);
				$('#headdone').setNumber(done);
				$('.content-done').addItem(txt,'删除');
            });
			
		}
	
	});
$.fn.extend({
	pages:function(total,cur,fun){
		$(this).jPaginator({ 
	    nbPages:total, 
	    selectedPage:cur,
	    overBtnLeft:'#left_over', 
	    overBtnRight:'#right_over', 
	    maxBtnLeft:'#left_max', 
	    maxBtnRight:'#right_max',
	    minSlidesForSlider:5, 
	    onPageClicked: fun
		//function(a,num) { 
	        //$("#page1").html("demo1 - page : "+num); 
	    //	alert(a);
		//}
	});  
		}
		
});

$.fn.extend({

	pages2:function(total,cur){
		$(this).jPaginator({ 
	    nbPages:total, 
	    selectedPage:cur,
	    overBtnLeft:'#left_over', 
	    overBtnRight:'#right_over', 
	    maxBtnLeft:'#left_max', 
	    maxBtnRight:'#right_max',
	    minSlidesForSlider:5, 
	    onPageClicked: function(a,num) { 

		}
	});  
		}	
	
});
$.fn.extend({

	debug:function(text){
		var ht = $(this).html()+'<br />';
		 $(this).html(ht + text);
		 $(this).css("display","block");
		}	
	
});

/////加载任务列表
function getTaskList(host, dbname,usr,pwd)
{
	var res = Qt.connectDB(host,dbname,usr,pwd);
	if ( res == 0 )
	{
		Qt.executeSQL("select getbydate('c016','2015-02-01','')");
		res = Qt.fieldValue(0,0);
		res = json2Array(res);
		return res;
	}else
	{
		Qt.msgBox('Ok','数据库连接失败');	
	}
}

function  json2Array(jstr)
{
	var jsobj = JSON.parse(jstr);
	var res = new Array;
	if ( jsobj instanceof Array)
	{
		
	}
	for ( key in jsobj )
	{
		//ss = JSON.stringify(jsobj[key]);
		//ss = ss.substr(0,100);
		ss = jsobj[key];
		res.push(ss);
	}
	return res;
}
function getType(obj)
{
	if ( obj instanceof Array )
	{
		return 'array';	
	}else{
		if ( obj == null )
		{
			return 'null';
		}else
		{
			return typeof(obj);
		}
	}
}

function transObject( jsobj)
{
	//$('.debug').debug('object');
	var result = '';
	for ( key in jsobj)
	{
		var tp = getType(jsobj[key]);
		//$('.debug').debug(key + ':' + tp);
		if ( tp == 'object' )
		{
			result += '<br />' + key + '为</br>' + transObject(jsobj[key]);	
		}else if ( tp == 'array' )
		{
			result += '<br />' + key + '分别为<br />' + transArray(jsobj[key]);
		}else if ( tp != 'null' ){
			result += key + '为' + jsobj[key] + ',';	
		}
	}
	//$('.debug').debug(result[result.length-1]);
	//$('.debug').debug(result.substr(result.length-1,1));
	if ( result[result.length-1] == ',' )
		{
			result = result.substr(0,result.length-1);	
		}
	result += '<br />';
	return result;
}
function transArray(jsarray)
{
	var result = '';
	for (i in jsarray)
	{
		for ( key in jsarray[i])
		{
			var tp = getType(jsarray[i][key]);
			//$('.debug').debug(key + ':' +tp);
			if ( tp  == 'object' )
			{
				result += key + '为<br />' + transObject(jsarray[i][key]);	
			}else if ( tp  == 'array' )
			{
				result += key + '分别为<br />' + transArray(jsarray[i][key]);
			}else if ( tp != 'null' )
			{
				result += key + '为' + jsarray[i][key] + ',';	
			}
		}
		if ( result[result.length-1] == ',' )
		{
			result = result.substr(0,result.length-1);	
		}
		//$('.debug').debug(result[result.length-1]);
		//$('.debug').debug(result.indexOf(',',result.length-2));
		result += ';<br />';
	}	
	
	result += '<br />';
	return result;
}
function translate2txt(jsobj)
{
	var result = '';
	if (  getType(jsobj) == 'object' )
	{
		
		return transObject( jsobj);
		
	}else if (  getType(jsobj) == 'array')
	{
		
		return transArray( jsobj)
	}
}