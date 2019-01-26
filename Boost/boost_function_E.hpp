namespace boost
{
namespace detail
{

inline void current_function_helper()
{
}

}

}

namespace boost
{

inline void throw_exception_assert_compatibility( std::exception const & ) { }

template<class E> __attribute__ ((__noreturn__)) inline void throw_exception( E const & e )
{
    throw_exception_assert_compatibility(e);
    throw enable_current_exception(enable_error_info(e));
}
    namespace
    exception_detail
    {
        template <class E>
        __attribute__ ((__noreturn__))
        void
        throw_exception_( E const & x, char const * current_function, char const * file, int line )
        {
            boost::throw_exception(
                set_info(
                    set_info(
                        set_info(
                            enable_error_info(x),
                            throw_function(current_function)),
                        throw_file(file)),
                    throw_line(line)));
        }
    }

}

namespace boost {

template<class T> T * get_pointer(T * p)
{
    return p;
}

template<class T> T * get_pointer(std::auto_ptr<T> const& p)
{
    return p.get();
}

namespace boost
{
namespace _mfi
{
template<class R, class T > class mf0
{
public:
    typedef R result_type;
    typedef T * argument_type;
private:
    typedef R ( T::*F) ();
    F f_;
    template<class U> R call(U & u, T const *) const
    {
        return (u.*f_)();
    }
    template<class U> R call(U & u, void const *) const
    {
        return (get_pointer(u)->*f_)();
    }
public:
    explicit mf0(F f): f_(f) {}
    R operator()(T * p) const
    {
        return (p->*f_)();
    }
    template<class U> R operator()(U & u) const
    {
        U const * p = 0;
        return call(u, p);
    }
    template<class U> R operator()(U const & u) const
    {
        U const * p = 0;
        return call(u, p);
    }
    R operator()(T & t) const
    {
        return (t.*f_)();
    }

    bool operator==(mf0 const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(mf0 const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

template<class R, class T > class cmf0
{
public:
    typedef R result_type;
    typedef T const * argument_type;
private:
    typedef R ( T::*F) () const;
    F f_;
    template<class U> R call(U & u, T const *) const
    {
        return (u.*f_)();
    }
    template<class U> R call(U & u, void const *) const
    {
        return (get_pointer(u)->*f_)();
    }
public:
    explicit cmf0(F f): f_(f) {}
    template<class U> R operator()(U const & u) const
    {
        U const * p = 0;
        return call(u, p);
    }
    R operator()(T const & t) const
    {
        return (t.*f_)();
    }
    bool operator==(cmf0 const & rhs) const
    {
        return f_ == rhs.f_;
    }
    bool operator!=(cmf0 const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

template<class R, class T, class A1 > class mf1
{
public:

    typedef R result_type;
    typedef T * first_argument_type;
    typedef A1 second_argument_type;

private:

    typedef R ( T::*F) (A1);
    F f_;

    template<class U, class B1> R call(U & u, T const *, B1 & b1) const
    {
        return (u.*f_)(b1);
    }

    template<class U, class B1> R call(U & u, void const *, B1 & b1) const
    {
        return (get_pointer(u)->*f_)(b1);
    }

public:

    explicit mf1(F f): f_(f) {}

    R operator()(T * p, A1 a1) const
    {
        return (p->*f_)(a1);
    }

    template<class U> R operator()(U & u, A1 a1) const
    {
        U const * p = 0;
        return call(u, p, a1);
    }

    template<class U> R operator()(U const & u, A1 a1) const
    {
        U const * p = 0;
        return call(u, p, a1);
    }

    R operator()(T & t, A1 a1) const
    {
        return (t.*f_)(a1);
    }

    bool operator==(mf1 const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(mf1 const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

template<class R, class T, class A1 > class cmf1
{
public:

    typedef R result_type;
    typedef T const * first_argument_type;
    typedef A1 second_argument_type;

private:

    typedef R ( T::*F) (A1) const;
    F f_;

    template<class U, class B1> R call(U & u, T const *, B1 & b1) const
    {
        return (u.*f_)(b1);
    }

    template<class U, class B1> R call(U & u, void const *, B1 & b1) const
    {
        return (get_pointer(u)->*f_)(b1);
    }

public:

    explicit cmf1(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1) const
    {
        U const * p = 0;
        return call(u, p, a1);
    }

    R operator()(T const & t, A1 a1) const
    {
        return (t.*f_)(a1);
    }

    bool operator==(cmf1 const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(cmf1 const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

}

template<class R, class T> _mfi::mf0<R, T> mem_fn(R ( T::*f) ())
{
    return _mfi::mf0<R, T>(f);
}

template<class R, class T> _mfi::cmf0<R, T> mem_fn(R ( T::*f) () const)
{
    return _mfi::cmf0<R, T>(f);
}

template<class R, class T, class A1> _mfi::mf1<R, T, A1> mem_fn(R ( T::*f) (A1))
{
    return _mfi::mf1<R, T, A1>(f);
}

template<class R, class T, class A1> _mfi::cmf1<R, T, A1> mem_fn(R ( T::*f) (A1) const)
{
    return _mfi::cmf1<R, T, A1>(f);
}


namespace _mfi
{

template<class R, class T> class dm
{
public:
    typedef R const & result_type;
    typedef T const * argument_type;
private:
    typedef R (T::*F);
    F f_;
    template<class U> R const & call(U & u, T const *) const
    {
        return (u.*f_);
    }
    template<class U> R const & call(U & u, void const *) const
    {
        return (get_pointer(u)->*f_);
    }
public:
    explicit dm(F f): f_(f) {}
    R & operator()(T * p) const
    {
        return (p->*f_);
    }
    R const & operator()(T const * p) const
    {
        return (p->*f_);
    }
    template<class U> R const & operator()(U const & u) const
    {
        return call(u, &u);
    }
    R & operator()(T & t) const
    {
        return (t.*f_);
    }
    R const & operator()(T const & t) const
    {
        return (t.*f_);
    }
    bool operator==(dm const & rhs) const
    {
        return f_ == rhs.f_;
    }
    bool operator!=(dm const & rhs) const
    {
        return f_ != rhs.f_;
    }
};
}

template<class R, class T> _mfi::dm<R, T> mem_fn(R T::*f)
{
    return _mfi::dm<R, T>(f);
}

}

namespace boost {
  namespace detail {
    namespace function {
      template<
        typename FunctionPtr,
        typename R
       
        >
      struct function_invoker0
      {
        static R invoke(function_buffer& function_ptr
                        )
        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
          return f();
        }
      };

      template<
        typename FunctionPtr,
        typename R
       
        >
      struct void_function_invoker0
      {
        static void
        invoke(function_buffer& function_ptr
               )

        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
          f();
        }
      };

      template<
        typename FunctionObj,
        typename R
       
      >
      struct function_obj_invoker0
      {
        static R invoke(function_buffer& function_obj_ptr
                        )

        {
          FunctionObj* f;
          if (function_allows_small_object_optimization<FunctionObj>::value)
            f = reinterpret_cast<FunctionObj*>(&function_obj_ptr.data);
          else
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          return (*f)();
        }
      };

      template<
        typename FunctionObj,
        typename R
       
      >
      struct void_function_obj_invoker0
      {
        static void
        invoke(function_buffer& function_obj_ptr
               )

        {
          FunctionObj* f;
          if (function_allows_small_object_optimization<FunctionObj>::value)
            f = reinterpret_cast<FunctionObj*>(&function_obj_ptr.data);
          else
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          (*f)();
        }
      };

      template<
        typename FunctionObj,
        typename R
       
      >
      struct function_ref_invoker0
      {
        static R invoke(function_buffer& function_obj_ptr
                        )

        {
          FunctionObj* f =
            reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          return (*f)();
        }
      };

      template<
        typename FunctionObj,
        typename R
       
      >
      struct void_function_ref_invoker0
      {
        static void
        invoke(function_buffer& function_obj_ptr
               )

        {
          FunctionObj* f =
            reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          (*f)();
        }
      };
      template<
        typename FunctionPtr,
        typename R
       
      >
      struct get_function_invoker0
      {
        typedef typename mpl::if_c<(is_void<R>::value),
                            void_function_invoker0<
                            FunctionPtr,
                            R
                           
                          >,
                          function_invoker0<
                            FunctionPtr,
                            R
                           
                          >
                       >::type type;
      };

      template<
        typename FunctionObj,
        typename R
       
       >
      struct get_function_obj_invoker0
      {
        typedef typename mpl::if_c<(is_void<R>::value),
                            void_function_obj_invoker0<
                            FunctionObj,
                            R
                           
                          >,
                          function_obj_invoker0<
                            FunctionObj,
                            R
                           
                          >
                       >::type type;
      };

      template<
        typename FunctionObj,
        typename R
       
       >
      struct get_function_ref_invoker0
      {
        typedef typename mpl::if_c<(is_void<R>::value),
                            void_function_ref_invoker0<
                            FunctionObj,
                            R
                           
                          >,
                          function_ref_invoker0<
                            FunctionObj,
                            R
                           
                          >
                       >::type type;
      };
      template<typename Tag>
      struct get_invoker0 { };

      template<>
      struct get_invoker0<function_ptr_tag>
      {
        template<typename FunctionPtr,
                 typename R >
        struct apply
        {
          typedef typename get_function_invoker0<
                             FunctionPtr,
                             R
                            
                           >::type
            invoker_type;

          typedef functor_manager<FunctionPtr> manager_type;
        };

        template<typename FunctionPtr,
                 typename R ,
                 typename Allocator>
        struct apply_a
        {
          typedef typename get_function_invoker0<
                             FunctionPtr,
                             R
                            
                           >::type
            invoker_type;

          typedef functor_manager<FunctionPtr> manager_type;
        };
      };

      template<>
      struct get_invoker0<function_obj_tag>
      {
        template<typename FunctionObj,
                 typename R >
        struct apply
        {
          typedef typename get_function_obj_invoker0<
                             FunctionObj,
                             R
                            
                           >::type
            invoker_type;

          typedef functor_manager<FunctionObj> manager_type;
        };

        template<typename FunctionObj,
                 typename R ,
                 typename Allocator>
        struct apply_a
        {
          typedef typename get_function_obj_invoker0<
                             FunctionObj,
                             R
                            
                           >::type
            invoker_type;

          typedef functor_manager_a<FunctionObj, Allocator> manager_type;
        };
      };

      template<>
      struct get_invoker0<function_obj_ref_tag>
      {
        template<typename RefWrapper,
                 typename R >
        struct apply
        {
          typedef typename get_function_ref_invoker0<
                             typename RefWrapper::type,
                             R
                            
                           >::type
            invoker_type;

          typedef reference_manager<typename RefWrapper::type> manager_type;
        };

        template<typename RefWrapper,
                 typename R ,
                 typename Allocator>
        struct apply_a
        {
          typedef typename get_function_ref_invoker0<
                             typename RefWrapper::type,
                             R
                            
                           >::type
            invoker_type;

          typedef reference_manager<typename RefWrapper::type> manager_type;
        };
      };

      template<typename R >
      struct basic_vtable0
      {
        typedef R result_type;
        typedef result_type (*invoker_type)(function_buffer&
                                           
                                            );
        template<typename F>
        bool assign_to(F f, function_buffer& functor) const
        {
          typedef typename get_function_tag<F>::type tag;
          return assign_to(f, functor, tag());
        }
        template<typename F,typename Allocator>
        bool assign_to_a(F f, function_buffer& functor, Allocator a) const
        {
          typedef typename get_function_tag<F>::type tag;
          return assign_to_a(f, functor, a, tag());
        }

        void clear(function_buffer& functor) const
        {
          if (base.manager)
            base.manager(functor, functor, destroy_functor_tag);
        }

      private:

        template<typename FunctionPtr>
        bool
        assign_to(FunctionPtr f, function_buffer& functor, function_ptr_tag) const
        {
          this->clear(functor);
          if (f) {


            functor.func_ptr = reinterpret_cast<void (*)()>(f);
            return true;
          } else {
            return false;
          }
        }
        template<typename FunctionPtr,typename Allocator>
        bool
        assign_to_a(FunctionPtr f, function_buffer& functor, Allocator, function_ptr_tag) const
        {
          return assign_to(f,functor,function_ptr_tag());
        }

        template<typename FunctionObj>
        void
        assign_functor(FunctionObj f, function_buffer& functor, mpl::true_) const
        {
          new (reinterpret_cast<void*>(&functor.data)) FunctionObj(f);
        }
        template<typename FunctionObj,typename Allocator>
        void
        assign_functor_a(FunctionObj f, function_buffer& functor, Allocator, mpl::true_) const
        {
          assign_functor(f,functor,mpl::true_());
        }

        template<typename FunctionObj>
        void
        assign_functor(FunctionObj f, function_buffer& functor, mpl::false_) const
        {
          functor.obj_ptr = new FunctionObj(f);
        }
        template<typename FunctionObj,typename Allocator>
        void
        assign_functor_a(FunctionObj f, function_buffer& functor, Allocator a, mpl::false_) const
        {
          typedef functor_wrapper<FunctionObj,Allocator> functor_wrapper_type;
          typedef typename Allocator::template rebind<functor_wrapper_type>::other
            wrapper_allocator_type;
          typedef typename wrapper_allocator_type::pointer wrapper_allocator_pointer_type;
          wrapper_allocator_type wrapper_allocator(a);
          wrapper_allocator_pointer_type copy = wrapper_allocator.allocate(1);
          wrapper_allocator.construct(copy, functor_wrapper_type(f,a));
          functor_wrapper_type* new_f = static_cast<functor_wrapper_type*>(copy);
          functor.obj_ptr = new_f;
        }

        template<typename FunctionObj>
        bool
        assign_to(FunctionObj f, function_buffer& functor, function_obj_tag) const
        {
          if (!boost::detail::function::has_empty_target(boost::addressof(f))) {
            assign_functor(f, functor,
                           mpl::bool_<(function_allows_small_object_optimization<FunctionObj>::value)>());
            return true;
          } else {
            return false;
          }
        }
        template<typename FunctionObj,typename Allocator>
        bool
        assign_to_a(FunctionObj f, function_buffer& functor, Allocator a, function_obj_tag) const
        {
          if (!boost::detail::function::has_empty_target(boost::addressof(f))) {
            assign_functor_a(f, functor, a,
                           mpl::bool_<(function_allows_small_object_optimization<FunctionObj>::value)>());
            return true;
          } else {
            return false;
          }
        }

        template<typename FunctionObj>
        bool
        assign_to(const reference_wrapper<FunctionObj>& f,
                  function_buffer& functor, function_obj_ref_tag) const
        {
          functor.obj_ref.obj_ptr = (void *)(f.get_pointer());
          functor.obj_ref.is_const_qualified = is_const<FunctionObj>::value;
          functor.obj_ref.is_volatile_qualified = is_volatile<FunctionObj>::value;
          return true;
        }
        template<typename FunctionObj,typename Allocator>
        bool
        assign_to_a(const reference_wrapper<FunctionObj>& f,
                  function_buffer& functor, Allocator, function_obj_ref_tag) const
        {
          return assign_to(f,functor,function_obj_ref_tag());
        }

      public:
        vtable_base base;
        invoker_type invoker;
      };
    }
  }

  template<
    typename R
  >
  class function0 : public function_base
  {
  public:
    typedef R result_type;
  private:
    typedef boost::detail::function::basic_vtable0<
              R >
      vtable_type;

    vtable_type* get_vtable() const {
      return reinterpret_cast<vtable_type*>(
               reinterpret_cast<std::size_t>(vtable) & ~static_cast<std::size_t>(0x01));
    }

    struct clear_type {};

  public:
    static const int args = 0;

    template<typename Args>
    struct sig
    {
      typedef result_type type;
    };
    static const int arity = 0;

    typedef function0 self_type;

    function0() : function_base() { }

    template<typename Functor>
    function0(Functor f

                            ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                             (is_integral<Functor>::value)>::value),
                                        int>::type = 0

                            ) :
      function_base()
    {
      this->assign_to(f);
    }
    template<typename Functor,typename Allocator>
    function0(Functor f, Allocator a

                            ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                             (is_integral<Functor>::value)>::value),
                                        int>::type = 0

                            ) :
      function_base()
    {
      this->assign_to_a(f,a);
    }

    function0(clear_type*) : function_base() { }
    function0(const function0& f) : function_base()
    {
      this->assign_to_own(f);
    }

    ~function0() { clear(); }

    result_type operator()() const
    {
      if (this->empty())
        boost::throw_exception(bad_function_call());

      return get_vtable()->invoker
               (this->functor );
    }

    template<typename Functor>

    typename enable_if_c<
               (boost::type_traits::ice_not<
                 (is_integral<Functor>::value)>::value),
               function0&>::type

    operator=(Functor f)
    {
      this->clear();
      { try {
        this->assign_to(f);
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
      return *this;
    }
    template<typename Functor,typename Allocator>
    void assign(Functor f, Allocator a)
    {
      this->clear();
      { try{
        this->assign_to_a(f,a);
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
    }

    function0& operator=(clear_type*)
    {
      this->clear();
      return *this;
    }

    function0& operator=(const function0& f)
    {
      if (&f == this)
        return *this;

      this->clear();
      { try {
        this->assign_to_own(f);
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
      return *this;
    }

    void swap(function0& other)
    {
      if (&other == this)
        return;

      function0 tmp;
      tmp.move_assign(*this);
      this->move_assign(other);
      other.move_assign(tmp);
    }

    void clear()
    {
      if (vtable) {
        if (!this->has_trivial_copy_and_destroy())
          get_vtable()->clear(this->functor);
        vtable = 0;
      }
    }

  private:
    struct dummy {
      void nonnull() {}
    };

    typedef void (dummy::*safe_bool)();

  public:
    operator safe_bool () const
      { return (this->empty())? 0 : &dummy::nonnull; }

    bool operator!() const
      { return this->empty(); }
  private:
    void assign_to_own(const function0& f)
    {
      if (!f.empty()) {
        this->vtable = f.vtable;
        if (this->has_trivial_copy_and_destroy())
          this->functor = f.functor;
        else
          get_vtable()->base.manager(f.functor, this->functor,
                                     boost::detail::function::clone_functor_tag);
      }
    }

    template<typename Functor>
    void assign_to(Functor f)
    {
      using detail::function::vtable_base;

      typedef typename detail::function::get_function_tag<Functor>::type tag;
      typedef detail::function::get_invoker0<tag> get_invoker;
      typedef typename get_invoker::
                         template apply<Functor, R
                        >
        handler_type;

      typedef typename handler_type::invoker_type invoker_type;
      typedef typename handler_type::manager_type manager_type;
      static const vtable_type stored_vtable =
        { { &manager_type::manage }, &invoker_type::invoke };

      if (stored_vtable.assign_to(f, functor)) {
        std::size_t value = reinterpret_cast<std::size_t>(&stored_vtable.base);

        if (boost::has_trivial_copy_constructor<Functor>::value &&
            boost::has_trivial_destructor<Functor>::value &&
            detail::function::function_allows_small_object_optimization<Functor>::value)
          value |= static_cast<std::size_t>(0x01);
        vtable = reinterpret_cast<detail::function::vtable_base *>(value);
      } else
        vtable = 0;
    }

    template<typename Functor,typename Allocator>
    void assign_to_a(Functor f,Allocator a)
    {
      using detail::function::vtable_base;

      typedef typename detail::function::get_function_tag<Functor>::type tag;
      typedef detail::function::get_invoker0<tag> get_invoker;
      typedef typename get_invoker::
                         template apply_a<Functor, R
                         ,
                         Allocator>
        handler_type;

      typedef typename handler_type::invoker_type invoker_type;
      typedef typename handler_type::manager_type manager_type;
      static const vtable_type stored_vtable =
        { { &manager_type::manage }, &invoker_type::invoke };

      if (stored_vtable.assign_to_a(f, functor, a)) {
        std::size_t value = reinterpret_cast<std::size_t>(&stored_vtable.base);

        if (boost::has_trivial_copy_constructor<Functor>::value &&
            boost::has_trivial_destructor<Functor>::value &&
            detail::function::function_allows_small_object_optimization<Functor>::value)
          value |= static_cast<std::size_t>(0x01);
        vtable = reinterpret_cast<detail::function::vtable_base *>(value);
      } else
        vtable = 0;
    }

    void move_assign(function0& f)
    {
      if (&f == this)
        return;

      { try {
        if (!f.empty()) {
          this->vtable = f.vtable;
          if (this->has_trivial_copy_and_destroy())
            this->functor = f.functor;
          else
            get_vtable()->base.manager(f.functor, this->functor,
                                     boost::detail::function::move_functor_tag);
          f.vtable = 0;
        } else {
          clear();
        }
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
    }
  };

  template<typename R >
  inline void swap(function0<
                     R
                    
                   >& f1,
                   function0<
                     R
                    
                   >& f2)
  {
    f1.swap(f2);
  }

template<typename R >
  void operator==(const function0<
                          R
                          >&,
                  const function0<
                          R
                          >&);
template<typename R >
  void operator!=(const function0<
                          R
                          >&,
                  const function0<
                          R
                          >& );
template<typename R
         >
class function<R (void)>
  : public function0<R >
{
  typedef function0<R > base_type;
  typedef function self_type;
  struct clear_type {};
public:
  function() : base_type() {}
  template<typename Functor>
  function(Functor f

           ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                          (is_integral<Functor>::value)>::value),
                       int>::type = 0

           ) :
    base_type(f)
  {
  }
  template<typename Functor,typename Allocator>
  function(Functor f, Allocator a

           ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                          (is_integral<Functor>::value)>::value),
                       int>::type = 0

           ) :
    base_type(f,a)
  {
  }

  function(clear_type*) : base_type() {}
  function(const self_type& f) : base_type(static_cast<const base_type&>(f)){}
  function(const base_type& f) : base_type(static_cast<const base_type&>(f)){}

  self_type& operator=(const self_type& f)
  {
    self_type(f).swap(*this);
    return *this;
  }

  template<typename Functor>

  typename enable_if_c<
                            (boost::type_traits::ice_not<
                         (is_integral<Functor>::value)>::value),
                      self_type&>::type



  operator=(Functor f)
  {
    self_type(f).swap(*this);
    return *this;
  }


  self_type& operator=(clear_type*)
  {
    this->clear();
    return *this;
  }


  self_type& operator=(const base_type& f)
  {
    self_type(f).swap(*this);
    return *this;
  }
};

}
namespace boost {
  namespace detail {
    namespace function {
      template<
        typename FunctionPtr,
        typename R ,
        typename T0
        >
      struct function_invoker1
      {
        static R invoke(function_buffer& function_ptr ,
                        T0 a0)
        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
          return f( a0);
        }
      };

      template<
        typename FunctionPtr,
        typename R ,
        typename T0
        >
      struct void_function_invoker1
      {
        static void
        invoke(function_buffer& function_ptr ,
               T0 a0)

        {
          FunctionPtr f = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
          f( a0);
        }
      };

      template<
        typename FunctionObj,
        typename R ,
        typename T0
      >
      struct function_obj_invoker1
      {
        static R invoke(function_buffer& function_obj_ptr ,
                        T0 a0)

        {
          FunctionObj* f;
          if (function_allows_small_object_optimization<FunctionObj>::value)
            f = reinterpret_cast<FunctionObj*>(&function_obj_ptr.data);
          else
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          return (*f)( a0);
        }
      };

      template<
        typename FunctionObj,
        typename R ,
        typename T0
      >
      struct void_function_obj_invoker1
      {
        static void
        invoke(function_buffer& function_obj_ptr ,
               T0 a0)

        {
          FunctionObj* f;
          if (function_allows_small_object_optimization<FunctionObj>::value)
            f = reinterpret_cast<FunctionObj*>(&function_obj_ptr.data);
          else
            f = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          (*f)( a0);
        }
      };

      template<
        typename FunctionObj,
        typename R ,
        typename T0
      >
      struct function_ref_invoker1
      {
        static R invoke(function_buffer& function_obj_ptr ,
                        T0 a0)

        {
          FunctionObj* f =
            reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          return (*f)( a0);
        }
      };

      template<
        typename FunctionObj,
        typename R ,
        typename T0
      >
      struct void_function_ref_invoker1
      {
        static void
        invoke(function_buffer& function_obj_ptr ,
               T0 a0)

        {
          FunctionObj* f =
            reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
          (*f)( a0);
        }
      };

      template<
        typename MemberPtr,
        typename R ,
        typename T0
      >
      struct function_mem_invoker1
      {
        static R invoke(function_buffer& function_obj_ptr ,
                        T0 a0)

        {
          MemberPtr* f =
            reinterpret_cast<MemberPtr*>(&function_obj_ptr.data);
          return boost::mem_fn(*f)( a0);
        }
      };

      template<
        typename MemberPtr,
        typename R ,
        typename T0
      >
      struct function_void_mem_invoker1
      {
        static void
        invoke(function_buffer& function_obj_ptr ,
               T0 a0)

        {
          MemberPtr* f =
            reinterpret_cast<MemberPtr*>(&function_obj_ptr.data);
          boost::mem_fn(*f)( a0);
        }
      };

      template<
        typename FunctionPtr,
        typename R ,
        typename T0
      >
      struct get_function_invoker1
      {
        typedef typename mpl::if_c<(is_void<R>::value),
                            void_function_invoker1<
                            FunctionPtr,
                            R ,
                            T0
                          >,
                          function_invoker1<
                            FunctionPtr,
                            R ,
                            T0
                          >
                       >::type type;
      };

      template<
        typename FunctionObj,
        typename R ,
        typename T0
       >
      struct get_function_obj_invoker1
      {
        typedef typename mpl::if_c<(is_void<R>::value),
                            void_function_obj_invoker1<
                            FunctionObj,
                            R ,
                            T0
                          >,
                          function_obj_invoker1<
                            FunctionObj,
                            R ,
                            T0
                          >
                       >::type type;
      };

      template<
        typename FunctionObj,
        typename R ,
        typename T0
       >
      struct get_function_ref_invoker1
      {
        typedef typename mpl::if_c<(is_void<R>::value),
                            void_function_ref_invoker1<
                            FunctionObj,
                            R ,
                            T0
                          >,
                          function_ref_invoker1<
                            FunctionObj,
                            R ,
                            T0
                          >
                       >::type type;
      };



      template<
        typename MemberPtr,
        typename R ,
        typename T0
       >
      struct get_member_invoker1
      {
        typedef typename mpl::if_c<(is_void<R>::value),
                            function_void_mem_invoker1<
                            MemberPtr,
                            R ,
                            T0
                          >,
                          function_mem_invoker1<
                            MemberPtr,
                            R ,
                            T0
                          >
                       >::type type;
      };

      template<typename Tag>
      struct get_invoker1 { };


      template<>
      struct get_invoker1<function_ptr_tag>
      {
        template<typename FunctionPtr,
                 typename R , typename T0>
        struct apply
        {
          typedef typename get_function_invoker1<
                             FunctionPtr,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef functor_manager<FunctionPtr> manager_type;
        };

        template<typename FunctionPtr,
                 typename R , typename T0,
                 typename Allocator>
        struct apply_a
        {
          typedef typename get_function_invoker1<
                             FunctionPtr,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef functor_manager<FunctionPtr> manager_type;
        };
      };

      template<>
      struct get_invoker1<member_ptr_tag>
      {
        template<typename MemberPtr,
                 typename R , typename T0>
        struct apply
        {
          typedef typename get_member_invoker1<
                             MemberPtr,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef functor_manager<MemberPtr> manager_type;
        };

        template<typename MemberPtr,
                 typename R , typename T0,
                 typename Allocator>
        struct apply_a
        {
          typedef typename get_member_invoker1<
                             MemberPtr,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef functor_manager<MemberPtr> manager_type;
        };
      };

      template<>
      struct get_invoker1<function_obj_tag>
      {
        template<typename FunctionObj,
                 typename R , typename T0>
        struct apply
        {
          typedef typename get_function_obj_invoker1<
                             FunctionObj,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef functor_manager<FunctionObj> manager_type;
        };

        template<typename FunctionObj,
                 typename R , typename T0,
                 typename Allocator>
        struct apply_a
        {
          typedef typename get_function_obj_invoker1<
                             FunctionObj,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef functor_manager_a<FunctionObj, Allocator> manager_type;
        };
      };


      template<>
      struct get_invoker1<function_obj_ref_tag>
      {
        template<typename RefWrapper,
                 typename R , typename T0>
        struct apply
        {
          typedef typename get_function_ref_invoker1<
                             typename RefWrapper::type,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef reference_manager<typename RefWrapper::type> manager_type;
        };

        template<typename RefWrapper,
                 typename R , typename T0,
                 typename Allocator>
        struct apply_a
        {
          typedef typename get_function_ref_invoker1<
                             typename RefWrapper::type,
                             R ,
                             T0
                           >::type
            invoker_type;

          typedef reference_manager<typename RefWrapper::type> manager_type;
        };
      };

      template<typename R , typename T0>
      struct basic_vtable1
      {
        typedef R result_type;
        typedef result_type (*invoker_type)(function_buffer&
                                            ,
                                            T0);
        template<typename F>
        bool assign_to(F f, function_buffer& functor) const
        {
          typedef typename get_function_tag<F>::type tag;
          return assign_to(f, functor, tag());
        }
        template<typename F,typename Allocator>
        bool assign_to_a(F f, function_buffer& functor, Allocator a) const
        {
          typedef typename get_function_tag<F>::type tag;
          return assign_to_a(f, functor, a, tag());
        }

        void clear(function_buffer& functor) const
        {
          if (base.manager)
            base.manager(functor, functor, destroy_functor_tag);
        }

      private:

        template<typename FunctionPtr>
        bool
        assign_to(FunctionPtr f, function_buffer& functor, function_ptr_tag) const
        {
          this->clear(functor);
          if (f) {


            functor.func_ptr = reinterpret_cast<void (*)()>(f);
            return true;
          } else {
            return false;
          }
        }
        template<typename FunctionPtr,typename Allocator>
        bool
        assign_to_a(FunctionPtr f, function_buffer& functor, Allocator, function_ptr_tag) const
        {
          return assign_to(f,functor,function_ptr_tag());
        }

        template<typename MemberPtr>
        bool assign_to(MemberPtr f, function_buffer& functor, member_ptr_tag) const
        {
          if (f) {
            this->assign_to(boost::mem_fn(f), functor);
            return true;
          } else {
            return false;
          }
        }
        template<typename MemberPtr,typename Allocator>
        bool assign_to_a(MemberPtr f, function_buffer& functor, Allocator a, member_ptr_tag) const
        {
          if (f) {
            this->assign_to_a(boost::mem_fn(f), functor, a);
            return true;
          } else {
            return false;
          }
        }

        template<typename FunctionObj>
        void
        assign_functor(FunctionObj f, function_buffer& functor, mpl::true_) const
        {
          new (reinterpret_cast<void*>(&functor.data)) FunctionObj(f);
        }
        template<typename FunctionObj,typename Allocator>
        void
        assign_functor_a(FunctionObj f, function_buffer& functor, Allocator, mpl::true_) const
        {
          assign_functor(f,functor,mpl::true_());
        }

        template<typename FunctionObj>
        void
        assign_functor(FunctionObj f, function_buffer& functor, mpl::false_) const
        {
          functor.obj_ptr = new FunctionObj(f);
        }
        template<typename FunctionObj,typename Allocator>
        void
        assign_functor_a(FunctionObj f, function_buffer& functor, Allocator a, mpl::false_) const
        {
          typedef functor_wrapper<FunctionObj,Allocator> functor_wrapper_type;
          typedef typename Allocator::template rebind<functor_wrapper_type>::other
            wrapper_allocator_type;
          typedef typename wrapper_allocator_type::pointer wrapper_allocator_pointer_type;
          wrapper_allocator_type wrapper_allocator(a);
          wrapper_allocator_pointer_type copy = wrapper_allocator.allocate(1);
          wrapper_allocator.construct(copy, functor_wrapper_type(f,a));
          functor_wrapper_type* new_f = static_cast<functor_wrapper_type*>(copy);
          functor.obj_ptr = new_f;
        }

        template<typename FunctionObj>
        bool
        assign_to(FunctionObj f, function_buffer& functor, function_obj_tag) const
        {
          if (!boost::detail::function::has_empty_target(boost::addressof(f))) {
            assign_functor(f, functor,
                           mpl::bool_<(function_allows_small_object_optimization<FunctionObj>::value)>());
            return true;
          } else {
            return false;
          }
        }
        template<typename FunctionObj,typename Allocator>
        bool
        assign_to_a(FunctionObj f, function_buffer& functor, Allocator a, function_obj_tag) const
        {
          if (!boost::detail::function::has_empty_target(boost::addressof(f))) {
            assign_functor_a(f, functor, a,
                           mpl::bool_<(function_allows_small_object_optimization<FunctionObj>::value)>());
            return true;
          } else {
            return false;
          }
        }

        template<typename FunctionObj>
        bool
        assign_to(const reference_wrapper<FunctionObj>& f,
                  function_buffer& functor, function_obj_ref_tag) const
        {
          functor.obj_ref.obj_ptr = (void *)(f.get_pointer());
          functor.obj_ref.is_const_qualified = is_const<FunctionObj>::value;
          functor.obj_ref.is_volatile_qualified = is_volatile<FunctionObj>::value;
          return true;
        }
        template<typename FunctionObj,typename Allocator>
        bool
        assign_to_a(const reference_wrapper<FunctionObj>& f,
                  function_buffer& functor, Allocator, function_obj_ref_tag) const
        {
          return assign_to(f,functor,function_obj_ref_tag());
        }

      public:
        vtable_base base;
        invoker_type invoker;
      };
    }
  }

  template<
    typename R ,
    typename T0
  >
  class function1 : public function_base
    , public std::unary_function<T0,R>
  {
  public:
    typedef R result_type;
  private:
    typedef boost::detail::function::basic_vtable1<
              R , T0>
      vtable_type;

    vtable_type* get_vtable() const {
      return reinterpret_cast<vtable_type*>(
               reinterpret_cast<std::size_t>(vtable) & ~static_cast<std::size_t>(0x01));
    }
    struct clear_type {};
  public:
    static const int args = 1;
    template<typename Args>
    struct sig
    {
      typedef result_type type;
    };
    typedef T0 argument_type;
    static const int arity = 1;
    typedef T0 arg1_type;
    typedef function1 self_type;
    function1() : function_base() { }

    template<typename Functor>
    function1(Functor f
                            ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                             (is_integral<Functor>::value)>::value),
                                        int>::type = 0

                            ) :
      function_base()
    {
      this->assign_to(f);
    }
    template<typename Functor,typename Allocator>
    function1(Functor f, Allocator a

                            ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                             (is_integral<Functor>::value)>::value),
                                        int>::type = 0

                            ) :
      function_base()
    {
      this->assign_to_a(f,a);
    }

    function1(clear_type*) : function_base() { }
    function1(const function1& f) : function_base()
    {
      this->assign_to_own(f);
    }
    ~function1() { clear(); }

    result_type operator()( T0 a0) const
    {
      if (this->empty())
        boost::throw_exception(bad_function_call());

      return get_vtable()->invoker
               (this->functor , a0);
    }
    template<typename Functor>

    typename enable_if_c<
               (boost::type_traits::ice_not<
                 (is_integral<Functor>::value)>::value),
               function1&>::type
    operator=(Functor f)
    {
      this->clear();
      { try {
        this->assign_to(f);
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
      return *this;
    }
    template<typename Functor,typename Allocator>
    void assign(Functor f, Allocator a)
    {
      this->clear();
      { try{
        this->assign_to_a(f,a);
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
    }

    function1& operator=(clear_type*)
    {
      this->clear();
      return *this;
    }

    function1& operator=(const function1& f)
    {
      if (&f == this)
        return *this;

      this->clear();
      { try {
        this->assign_to_own(f);
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
      return *this;
    }

    void swap(function1& other)
    {
      if (&other == this)
        return;

      function1 tmp;
      tmp.move_assign(*this);
      this->move_assign(other);
      other.move_assign(tmp);
    }

    void clear()
    {
      if (vtable) {
        if (!this->has_trivial_copy_and_destroy())
          get_vtable()->clear(this->functor);
        vtable = 0;
      }
    }

  private:
    struct dummy {
      void nonnull() {}
    };

    typedef void (dummy::*safe_bool)();

  public:
    operator safe_bool () const
      { return (this->empty())? 0 : &dummy::nonnull; }

    bool operator!() const
      { return this->empty(); }

  private:
    void assign_to_own(const function1& f)
    {
      if (!f.empty()) {
        this->vtable = f.vtable;
        if (this->has_trivial_copy_and_destroy())
          this->functor = f.functor;
        else
          get_vtable()->base.manager(f.functor, this->functor,
                                     boost::detail::function::clone_functor_tag);
      }
    }

    template<typename Functor>
    void assign_to(Functor f)
    {
      using detail::function::vtable_base;

      typedef typename detail::function::get_function_tag<Functor>::type tag;
      typedef detail::function::get_invoker1<tag> get_invoker;
      typedef typename get_invoker::
                         template apply<Functor, R ,
                        T0>
        handler_type;

      typedef typename handler_type::invoker_type invoker_type;
      typedef typename handler_type::manager_type manager_type;
      static const vtable_type stored_vtable =
        { { &manager_type::manage }, &invoker_type::invoke };

      if (stored_vtable.assign_to(f, functor)) {
        std::size_t value = reinterpret_cast<std::size_t>(&stored_vtable.base);

        if (boost::has_trivial_copy_constructor<Functor>::value &&
            boost::has_trivial_destructor<Functor>::value &&
            detail::function::function_allows_small_object_optimization<Functor>::value)
          value |= static_cast<std::size_t>(0x01);
        vtable = reinterpret_cast<detail::function::vtable_base *>(value);
      } else
        vtable = 0;
    }

    template<typename Functor,typename Allocator>
    void assign_to_a(Functor f,Allocator a)
    {
      using detail::function::vtable_base;

      typedef typename detail::function::get_function_tag<Functor>::type tag;
      typedef detail::function::get_invoker1<tag> get_invoker;
      typedef typename get_invoker::
                         template apply_a<Functor, R ,
                         T0,
                         Allocator>
        handler_type;

      typedef typename handler_type::invoker_type invoker_type;
      typedef typename handler_type::manager_type manager_type;
      static const vtable_type stored_vtable =
        { { &manager_type::manage }, &invoker_type::invoke };

      if (stored_vtable.assign_to_a(f, functor, a)) {
        std::size_t value = reinterpret_cast<std::size_t>(&stored_vtable.base);

        if (boost::has_trivial_copy_constructor<Functor>::value &&
            boost::has_trivial_destructor<Functor>::value &&
            detail::function::function_allows_small_object_optimization<Functor>::value)
          value |= static_cast<std::size_t>(0x01);
        vtable = reinterpret_cast<detail::function::vtable_base *>(value);
      } else
        vtable = 0;
    }
    void move_assign(function1& f)
    {
      if (&f == this)
        return;

      { try {
        if (!f.empty()) {
          this->vtable = f.vtable;
          if (this->has_trivial_copy_and_destroy())
            this->functor = f.functor;
          else
            get_vtable()->base.manager(f.functor, this->functor,
                                     boost::detail::function::move_functor_tag);
          f.vtable = 0;
        } else {
          clear();
        }
      } catch(...) {
        vtable = 0;
        throw;;
      }
      }
    }
  };

  template<typename R , typename T0>
  inline void swap(function1<
                     R ,
                     T0
                   >& f1,
                   function1<
                     R ,
                     T0
                   >& f2)
  {
    f1.swap(f2);
  }

template<typename R , typename T0>
  void operator==(const function1<
                          R ,
                          T0>&,
                  const function1<
                          R ,
                          T0>&);
template<typename R , typename T0>
  void operator!=(const function1<
                          R ,
                          T0>&,
                  const function1<
                          R ,
                          T0>& );
template<typename R ,
         typename T0>
class function<R ( T0)>
  : public function1<R , T0>
{
  typedef function1<R , T0> base_type;
  typedef function self_type;

  struct clear_type {};

public:

  function() : base_type() {}

  template<typename Functor>
  function(Functor f
           ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                          (is_integral<Functor>::value)>::value),
                       int>::type = 0
           ) :
    base_type(f)
  {
  }
  template<typename Functor,typename Allocator>
  function(Functor f, Allocator a
           ,typename enable_if_c<
                            (boost::type_traits::ice_not<
                          (is_integral<Functor>::value)>::value),
                       int>::type = 0
           ) :
    base_type(f,a)
  {
  }

  function(clear_type*) : base_type() {}
  function(const self_type& f) : base_type(static_cast<const base_type&>(f)){}
  function(const base_type& f) : base_type(static_cast<const base_type&>(f)){}

  self_type& operator=(const self_type& f)
  {
    self_type(f).swap(*this);
    return *this;
  }

  template<typename Functor>
  typename enable_if_c<
                            (boost::type_traits::ice_not<
                         (is_integral<Functor>::value)>::value),
                      self_type&>::type
  operator=(Functor f)
  {
    self_type(f).swap(*this);
    return *this;
  }

  self_type& operator=(clear_type*)
  {
    this->clear();
    return *this;
  }


  self_type& operator=(const base_type& f)
  {
    self_type(f).swap(*this);
    return *this;
  }
};
}

namespace boost {
  namespace detail {
    namespace function {

      template<int Args> struct real_get_function_impl {};

      template<>
      struct real_get_function_impl<0>
      {
        template<
          typename R,
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy = empty_function_policy,
          typename Mixin = empty_function_mixin,
          typename Allocator = std::allocator<function_base>
        >
        struct params
        {
          typedef function0<R, Policy, Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<1>
      {
        template<
          typename R,
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy = empty_function_policy,
          typename Mixin = empty_function_mixin,
          typename Allocator = std::allocator<function_base>
        >
        struct params
        {
          typedef function1<R, T1, Policy, Mixin, Allocator> type;
        };
      };

      template<>
      struct real_get_function_impl<2>
      {
        template<
          typename R,
          typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9,
          typename T10,
          typename Policy = empty_function_policy,
          typename Mixin = empty_function_mixin,
          typename Allocator = std::allocator<function_base>
        >
        struct params
        {
          typedef function2<R, T1, T2, Policy, Mixin, Allocator> type;
        };
      };

      template<
        typename R,
        typename T1,
        typename T2,
        typename T3,
        typename T4,
        typename T5,
        typename T6,
        typename T7,
        typename T8,
        typename T9,
        typename T10,
        typename Policy = empty_function_policy,
        typename Mixin = empty_function_mixin,
        typename Allocator = std::allocator<function_base>
      >
      struct get_function_impl
      {
        typedef typename real_get_function_impl<
          (count_used_args<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::value)
          >::template params<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10,
                             Policy, Mixin, Allocator>::type
        type;
      };

  template<
    typename R,
    typename T1,
    typename T2,
    typename T3,
    typename T4,
    typename T5,
    typename T6,
    typename T7,
    typename T8,
    typename T9,
    typename T10,
    typename MyPolicy = empty_function_policy,
    typename MyMixin = empty_function_mixin,
    typename MyAllocator = std::allocator<function_base>
  >
  struct function_traits_builder
  {
    typedef typename get_function_impl<R, T1, T2, T3, T4, T5, T6, T7,
                                       T8, T9, T10, MyPolicy, MyMixin,
                                       MyAllocator>::type
      type;

    typedef MyPolicy policy_type;
    typedef MyMixin mixin_type;
    typedef MyAllocator allocator_type;


    template<typename Policy>
    struct policy :
        public function_traits_builder<R, T1, T2, T3, T4, T5, T6, T7, T8, T9,
                                       T10, Policy, mixin_type,
                                       allocator_type> {};

    template<typename Mixin>
    struct mixin :
        public function_traits_builder<R, T1, T2, T3, T4, T5, T6, T7, T8, T9,
                                       T10, policy_type, Mixin,
                                       allocator_type> {};

    template<typename Allocator>
    struct allocator :
        public function_traits_builder<R, T1, T2, T3, T4, T5, T6, T7, T8, T9,
                                       T10, policy_type, mixin_type,
                                       Allocator> {};
  };
    }
  }

  template<
    typename R,
    typename T1 = detail::function::unusable,
    typename T2 = detail::function::unusable,
    typename T3 = detail::function::unusable,
    typename T4 = detail::function::unusable,
    typename T5 = detail::function::unusable,
    typename T6 = detail::function::unusable,
    typename T7 = detail::function::unusable,
    typename T8 = detail::function::unusable,
    typename T9 = detail::function::unusable,
    typename T10 = detail::function::unusable
  >
  class function :
    public detail::function::get_function_impl<R, T1, T2, T3, T4, T5, T6, T7,
                                               T8, T9, T10>::type,
    public detail::function::function_traits_builder<R, T1, T2, T3, T4, T5, T6,
                                                     T7, T8, T9, T10>
  {
    typedef typename detail::function::get_function_impl<R, T1, T2, T3, T4, T5,
                                                         T6, T7, T8, T9, T10
                                                         >::type
      base_type;
  public:
    typedef typename base_type::policy_type policy_type;
    typedef typename base_type::mixin_type mixin_type;
    typedef typename base_type::allocator_type allocator_type;
    typedef function self_type;

    function() : base_type() {}

    template<typename Functor>
    function(const Functor& f) : base_type(f) {}

    function(const self_type& f) : base_type(static_cast<const base_type&>(f)){}

    template<typename Functor>
    function& operator=(const Functor& f)
    {
      self_type(f).swap(*this);
      return *this;
    }

    self_type& operator=(const base_type& f)
    {
      self_type(f).swap(*this);
      return *this;
    }

    self_type& operator=(const self_type& f)
    {
      self_type(f).swap(*this);
      return *this;
    }

    template<typename Functor>
    void set(const Functor& f)
    {
      self_type(f).swap(*this);
    }

    void set(const base_type& f)
    {
      self_type(f).swap(*this);
    }

    void set(const self_type& f)
    {
      self_type(f).swap(*this);
    }
  };

  template<typename R,
           typename T1,
           typename T2,
           typename T3,
           typename T4,
           typename T5,
           typename T6,
           typename T7,
           typename T8,
           typename T9,
           typename T10>
  inline void swap(function<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& f1,
                   function<R, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& f2)
  {
    f1.swap(f2);
  }
}
