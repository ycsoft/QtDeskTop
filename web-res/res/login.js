
// JavaScript Document
function caMouseIn(obj)
{
	obj.style.backgroundColor = "#FF8040";	
	tips(obj.id,"使用CA证书登录，无需输入用户名密码");
}
function caMouseOut(obj)
{
	outtips();
	obj.style.backgroundColor = "#CDCDCD";
}


function tips(id,str){

    t= getTop(document.getElementById(id))-document.getElementById(id).offsetHeight;

    l=  getLeft(document.getElementById(id));

    document.getElementById("tips").innerHTML="提示："+str;

    document.getElementById("tips").style.left=l+"px";

    document.getElementById("tips").style.top=t+"px";

    document.getElementById("tips").style.display="";

}

function outtips(){

    document.getElementById("tips").style.display='none';

}

//获取元素的纵坐标

    function getTop(e){

        var offset=e.offsetTop;

        if(e.offsetParent!=null) offset+=getTop(e.offsetParent);

        return offset;

    }

    //获取元素的横坐标

    function getLeft(e){

        var offset=e.offsetLeft;

        if(e.offsetParent!=null) offset+=getLeft(e.offsetParent);

        return offset;

    }