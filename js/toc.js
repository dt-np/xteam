$(function(){
  $(".toc-level-0 .toc-level-0 > a").click(function() {
    $(this).parent().find('> ol').slideToggle(200);

    return false;
  });

  $('label[for="toc-toggle"]').click(function() {
    $('.toc-container').slideToggle(500);
  });

  $(function(){
    $('.content h1,h2,h3,h4,h5,h6').each(function(){
      var toc = $(this);
      toc.attr('class', 'anchorable-toc');
    });
  });

  $(function(){
    $('.anchorable-toc').each(function(){
      var toc = $(this),
      id = toc.attr('id'),
      href = "#" + id,
      anchor = '<a class="toc-anchor" href="'+href+'"></a>';

      toc.prepend(anchor);
    });
  });
});
